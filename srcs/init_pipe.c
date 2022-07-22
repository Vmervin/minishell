/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:53:34 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/23 01:20:49 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int pipe_memfree(t_info info)
{
	int i;

	i = 0;
	while(info.env[i])
	{
		free(info.env[i]);
		i++;
	}
	free(info.env);
	free(info.path);
	free(info.pid);
	free(info.fdpipe);
	if (info.hd)
		free(info.hd);
	return (0);
}

// close pipes if failed
int	pipe_error(t_info *info, int i)
{
	int j;

	j = 0;
	perror("pipe");
	while (j < i)
	{
		close(info->fdpipe[j][0]);
		close(info->fdpipe[j][1]);
		j++;
	}	
	pipe_memfree(*info);
	return (1);
}

int init_pid(t_info *info, int len)
{
	int i;

	info->pid = malloc(len * sizeof(int));
	i = 0;
	while (i < len)
		info->pid[i++] = -1;
	return (0);
}

int init_pipe(t_info *info, int len, t_cmd *cmds)
{
	int i;

	info->res = 0;
	info->len = len;
	info->cmds = cmds;
	info->args = NULL;
	info->hd = NULL;
	info->tmpin = dup(0);
	info->tmpout = dup(1);
	info->fdpipe = malloc((len - 1) * sizeof(*info->fdpipe));
	i = 0;
	while (i < len - 1)
	{
		if (pipe(info->fdpipe[i++]) < 0)
			return (pipe_error(info, i));
	}
	info->env = list_to_env();
	info->path = get_var("PATH");
	init_pid(info, len);
	return (0);
}
