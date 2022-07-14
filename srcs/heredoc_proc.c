/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_proc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 21:37:14 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/09 22:30:12 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_heredoc(char *string, int append)
{
	t_parser	service;
	char		**val;

	service.tokens = NULL;
	service.string = string;
	service.error = 0;
	val = NULL;
	if (append == 1 && ft_strchr(string, '$'))
	{
		dollar_sign_token_search(&service.tokens, '$', string);
		val = extract_value(service.tokens, string);
		if (service.tokens && val)
			string = expand_for_real(service.tokens, string, val);
		ft_lstclear(&service.tokens, free);
		if (val)
			free(val);
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
	char	*out;

	line = readline("> ");
	out = NULL;
	while (line && !is_eof(line, eof))
	{
		line = expand_heredoc(line, append);
		// printf("imhere!\n");
		if (strcat_add(&out, line))
			mini_err(g_var.store, ERR_MALLOC0);
		free(line);
		line = readline("> ");
	}
	if (strcat_add(&out, "\n"))
		mini_err(g_var.store, ERR_MALLOC0);
	ft_putstr_fd(out, fd);
	free(line);
}
