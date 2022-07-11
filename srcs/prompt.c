/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:35:37 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/11 03:14:49 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*prompt_invitation(void)
{
	char	*prompt;

	prompt = ft_strjoin("[", get_var("USER"));
	prompt = ft_strjoin_free(prompt, ft_strdup("@"));
	prompt = ft_strjoin_free(prompt, ft_strdup(get_var("HOSTNAME")));
	prompt = ft_strjoin_free(prompt, ft_strdup("]$ "));
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

char	*rl_gets(void)
{
	char	*line;
	char	*prompt;
	struct 	sigaction	act;

	act.sa_handler = recieve;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGINT);
	sigaddset(&act.sa_mask, SIGQUIT);
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGINT, &act, NULL);
	prompt = prompt_invitation();
	line = readline(prompt);
	free(prompt);
	if (!line)
	{
		printf("exit(%s)", line);
		mini_err(g_var.store, 888);
	}
	if (*line != '\0')
		add_history(line);
	return (line);
}
