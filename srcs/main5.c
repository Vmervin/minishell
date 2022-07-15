/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 03:49:26 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/14 05:37:59 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

t_global	g_var;

int	pipe_exec_subfunc(t_store *st, t_cmd *cmds, int num)
{
	get_infile_fd(st, cmds, num);
	get_outfile_fd(st, cmds, num);
	st->last_result = execve(st->com[num], st->par[num], st->env);
	if (st->last_result == -1)
		mini_err(st, ERR_FOR_SUBFUNC);
	exit(0);
	return (0);
}

int	pipe_exec(t_store *st, t_cmd *cmds, int num)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid < 0)
		mini_err(st, ERR_FORK_INIT);
	if (pid == 0)
	{
		pipe_exec_subfunc(st, cmds, num);
	}
	else
	{
		if (num < st->size - 1)
			close(st->pip[num][1]);
		waitpid(pid, &status, 0);
		if (!WIFEXITED(status))
			mini_err(st, 102);
		if (WEXITSTATUS(status) == 103)
			mini_err(st, 102);
		g_var.last_exec = WEXITSTATUS(status);
	}
	return (pid);
}

int	main_loop(t_store *st, t_cmd *cmds, int status, int i)
{
	int	pid;

	malloc_appropriate_struct(st, cmds);
	create_appropriate_struct(st, cmds);
	if (!st->tempfile_dir)
		st->tempfile_dir = strjoin_char(get_var("HOME"),
				".minishell_tempfile", '/');
	if (!is_command_ok(st))
		return (0);
	if (st->size == 1 && built_in_check(st->par[0][0]))
	{
		g_var.last_exec = is_built_in(cmds->command);
		return (0);
	}
	while (++i < st->size)
	{
		pid = pipe_exec(st, cmds + i, i);
		if (pid == -1)
			break ;
	}
	i = -1;
	g_var.last_exec = WEXITSTATUS(status);
	return (0);
}

int	main(int args, char **argv, char **env)
{
	t_store	st;
	int		err;
	t_cmd	*cmds;
	char	*str;

	if (startup(&st, env, args, argv))
		return (0);
	while (1)
	{
		str = rl_gets();
		if (!str || !*str)
			continue ;
		cmds = parser(str, &err);
		st.list = cmds;
		if (err)
			continue ;
		st.env = list_to_env();
		st.path = ft_split(get_var("PATH"), ':');
		if (!st.path || !st.env)
			mini_err(&st, 0);
		st.path_size = get_void_size((void *)st.path);
		st.size = get_cmd_size(cmds);
		err = main_loop(&st, cmds, 0, -1);
	}
}
