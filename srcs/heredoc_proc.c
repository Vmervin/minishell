/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_proc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 21:37:14 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/22 23:09:02 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_heredoc(char *string, int append)
{
	t_parser	service;
	// char		**val;

	service.tokens = NULL;
	service.string = string;
	service.error = 0;
	// val = NULL;
	if (append == 1 && ft_strchr(string, '$'))
	{
		dollar_sign_token_search(&service.tokens, '$', string);
		string = extractor(string, &service);
		// val = extract_value(service.tokens, string);
		// if (service.tokens && val)
		// 	string = expand_for_real(service.tokens, string, val);
		ft_lstclear(&service.tokens, free);
		// if (val)
		// 	free(val);
	}
	return (string);
}

int	is_eof(char *line, char *eof)
{
	return (ft_strlen(eof) == ft_strlen(line)
		&& !ft_strncmp(eof, line, ft_strlen(eof)));
}

void	heredoc(char *eof, int fd, int append)
{
	char	*line;
	// char	*out;

	line = readline("> ");
	// out = NULL;
	while (line && !is_eof(line, eof))
	{
		line = expand_heredoc(line, append);
		// printf("imhere!\n");
		// if (strcat_add(&out, line))
		// 	mini_err(g_var.store, ERR_MALLOC0);
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
		line = readline("> ");
	}
	// if (strcat_add(&out, "\n"))
	// 	mini_err(g_var.store, ERR_MALLOC0);
	// ft_putstr_fd(out, fd);
	// ft_putchar_fd('\0', fd);
	// rl_replace_line("\0", 0);
	// ft_putstr_fd(line, 0);
	free(line);
}

int heredoc_proc(t_list *lst, t_info *info)
{
	int herdoc;

	info->fdin = dup(0);
	dup2(info->tmpin, 0);
	info->hd = ft_strjoin_free(get_var("HOME"), ft_strdup("/"));
	info->hd = ft_strjoin_free(info->hd, ft_strdup(".HERE_DOCUMENT"));
	herdoc = open(info->hd, O_WRONLY | O_CREAT | O_TRUNC, 0664);// need to close and then reopen
	heredoc(((t_file *)(lst->content))->name, herdoc, ((t_file *)(lst->content))->append);
	dup2(info->fdin, 0);
	close(info->fdin);
	close(herdoc);
	info->fdin = open(info->hd, O_RDONLY, 0664);
	return (0);
}