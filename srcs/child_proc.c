/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_proc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:56:18 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/23 22:21:25 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// close all fd in child
int	fd_closer(int num, int (*fdpipe)[2])
{
	int	i;

	i = 0;
	while (i < num)
	{
		close(fdpipe[i][0]);
		close(fdpipe[i][1]);
		i++;
	}
	return (0);
}

int	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
	return (0);
}

char	*get_path(char *args, char *path, int *error)
{
	char	*res;
	int		i;
	int		acc;
	char	**true_path;

	i = 0;
	true_path = ft_split(path, ':');
	while (true_path[i])
	{
		res = ft_strjoin(true_path[i], "/");
		res = ft_strjoin_free(res, ft_strdup(args));
		acc = access(res, F_OK);
		if (!acc)
		{
			free(args);
			free_path(true_path);
			return (res);
		}
		free(res);
		i++;
	}
	*error = error_mess(args, 3, strerror(errno));
	free_path(true_path);
	free(args);
	return (NULL);
}

int	exe_command(t_info *info)
{
	int	error;

	fd_closer(info->len - 1, info->fdpipe);
	error = 0;
	if (info->args[0])
	{
		if (access(info->args[0], X_OK))
			error = error_mess(info->args[0], 4, strerror(errno));
		execve(info->args[0], info->args, info->env);
	}
	exit(error);
}

int	child_birth(t_cmd *cmds, t_info *info, int i)
{
	int	error;

	error = 0;
	info->args = list_to_argv(cmds[i].command);
	if (!ft_strchr(info->args[0], '/') && info->path)
		info->args[0] = get_path(info->args[0], info->path, &error);
	if (!error)
		info->pid[i] = fork();
	if (!info->pid[i])
	{
		exe_command(info);
	}
	free_path(info->args);
	return (error);
}
