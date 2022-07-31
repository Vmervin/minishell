/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_proc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 21:37:14 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/31 19:31:48 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*expand_heredoc(char *string, int append)
{
	t_parser	service;

	service.tokens = NULL;
	service.string = string;
	service.error = 0;
	if (append == 1 && ft_strchr(string, '$'))
	{
		dollar_sign_token_search(&service.tokens, '$', string);
		string = extractor(string, &service);
		ft_lstclear(&service.tokens, free);
	}
	return (string);
}

static int	is_eof(char *line, char *eof)
{
	return (ft_strlen(eof) == ft_strlen(line)
		&& !ft_strncmp(eof, line, ft_strlen(eof)));
}

static void	heredoc(char *eof, int fd, int append)
{
	char	*line;

	line = readline("> ");
	while (line && !is_eof(line, eof))
	{
		line = expand_heredoc(line, append);
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
		line = readline("> ");
	}
	free(line);
}

// need to close and then reopen file
int	heredoc_proc(t_list *lst, t_info *info)
{
	int	herdoc;

	info->fdin = dup(0);
	dup2(info->tmpin, 0);
	info->hd = ft_strjoin_free(get_var("HOME"), ft_strdup("/"));
	info->hd = ft_strjoin_free(info->hd, ft_strdup(".HERE_DOCUMENT"));
	herdoc = open(info->hd, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	heredoc(((t_file *)(lst->content))->name, herdoc,
		((t_file *)(lst->content))->append);
	dup2(info->fdin, 0);
	close(info->fdin);
	close(herdoc);
	info->fdin = open(info->hd, O_RDONLY, 0664);
	return (0);
}
