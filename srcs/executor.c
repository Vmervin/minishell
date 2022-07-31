/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:40:52 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/31 19:32:39 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// set value for $? special parameter
static int	waitress(t_info *info, int i)
{
	int	error;

	if (info->pid[i] < 0)
		return (0);
	waitpid(info->pid[i], &error, 0);
	if (WIFEXITED(error))
		info->res = WEXITSTATUS(error);
	if (WIFSIGNALED(error))
		info->res = WTERMSIG(error) + 128;
	return (0);
}

static int	in_outpipe(t_info *info, int i, int in)
{
	if (in)
	{
		if (i < info->len - 1)
		{
			dup2(info->fdpipe[i][1], 1);
			close(info->fdpipe[i][1]);
		}
		else
			dup2(info->tmpout, 1);
	}
	else
	{
		if (i < info->len - 1)
		{
			dup2(info->fdpipe[i][0], 0);
			close(info->fdpipe[i][0]);
		}
	}
	return (0);
}

int	command_executor(t_cmd *cmds, t_info *info, int i)
{
	info->res = 0;
	in_outpipe(info, i, 1);
	open_loop(cmds[i], info);
	if (info->res)
		return (1);
	if (cmds[i].command)
	{
		if (built_in_check(((t_file *)cmds[i].command->content)->name))
			info->res = is_built_in(cmds[i].command, !i, info);
		else
			info->res = child_birth(cmds, info, i);
	}
	waitress(info, i);
	in_outpipe(info, i, 0);
	if (info->hd)
		unlink(info->hd);
	return (0);
}
