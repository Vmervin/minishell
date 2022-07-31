/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 19:42:33 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/31 19:27:29 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_global	g_var;

static int	cmdlen(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (!cmds[i].empty)
		i++;
	return (i);
}

int	main_loop(t_cmd *cmds, int len)
{
	int		i;
	t_info	info;

	i = 0;
	if (init_pipe(&info, len, cmds))
		return (1);
	while (i < len)
	{
		command_executor(cmds, &info, i);
		i++;
	}
	dup2(info.tmpin, 0);
	dup2(info.tmpout, 1);
	close(info.tmpin);
	close(info.tmpout);
	pipe_memfree(info);
	return (info.res);
}

// average leaks of readline library:
// still reachable: 113,611 bytes in 181 blocks
// still reachable: 113,751 bytes in 190 blocks
// still reachable: 119,096 bytes in 199 blocks
int	main(int argc, char **argv, char **env)
{
	int		err;
	t_cmd	*cmds;
	char	*str;

	(void)argc;
	(void)argv;
	env_to_list(env);
	while (1)
	{
		str = rl_gets();
		if (!str || !*str)
			continue ;
		cmds = parser(str, &err);
		if (err)
		{
			g_var.last_exec = err;
			command_memfree(cmds);
			free(str);
			continue ;
		}
		g_var.last_exec = main_loop(cmds, cmdlen(cmds));
		command_memfree(cmds);
		free(str);
	}
}
