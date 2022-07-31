/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:35:37 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/23 21:58:04 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*prompt_invitation(void)
{
	char	*prompt;
	char	*path;

	path = getcwd(NULL, 0);
	prompt = ft_strjoin("Mini[", getenv("USER"));
	prompt = ft_strjoin_free(prompt, ft_strdup("@"));
	prompt = ft_strjoin_free(prompt, ft_strdup(getenv("HOSTNAME")));
	prompt = ft_strjoin_free(prompt, ft_strdup(" "));
	prompt = ft_strjoin_free(prompt, ft_strdup(ft_strrchr(path, '/') + 1));
	prompt = ft_strjoin_free(prompt, ft_strdup("]$ "));
	free(path);
	return (prompt);
}

void	recieve(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	handler_set(struct sigaction *act)
{
	act->sa_handler = recieve;
	act->sa_flags = 0;
	sigemptyset(&act->sa_mask);
	sigaddset(&act->sa_mask, SIGINT);
	sigaddset(&act->sa_mask, SIGQUIT);
	sigaction(SIGQUIT, act, NULL);
	sigaction(SIGINT, act, NULL);
	sigaction(SIGTERM, act, NULL);
	return (0);
}

char	*rl_gets(void)
{
	char				*line;
	char				*prompt;
	struct sigaction	act;

	handler_set(&act);
	prompt = prompt_invitation();
	line = readline(prompt);
	free(prompt);
	if (!line)
	{
		ft_putstr_fd("exit: \n", 2);
		memfree(g_var.env);
		clear_history();
		exit(0);
	}
	if (line && *line != '\0')
		add_history(line);
	else
	{
		free(line);
		return (NULL);
	}
	return (line);
}
