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

int	get_infile_fd2(t_store *st, t_cmd *cmds)
{
	int		temp_fd;

	temp_fd = -1;
	temp_fd = get_infile_fd_cycle(st, cmds->infiles);
	temp_fd = open(st->tempfile_dir, O_RDONLY, 0664);
	if (dup2(temp_fd, 0) == -1)
		mini_err(st, ERR_SUB_PRCCESS);
	if (temp_fd != -1)
		close(temp_fd);
	return (0);
}

int	get_infile_fd(t_store *st, t_cmd *cmds, int num)
{
	if (num > 0)
		close(st->pip[num - 1][1]);
	if (cmds->infiles == NULL)
	{
		if (num == 0)
			return (0);
		if (dup2(st->pip[num - 1][0], 0) == -1)
			mini_err(st, ERR_SUB_PRCCESS);
		close(st->pip[num - 1][0]);
		return (0);
	}
	else
		get_infile_fd2(st, cmds);
	return (0);
}

int	get_outfile_fd2(t_store *st, t_cmd *cmds)
{
	t_list	*lst;
	int		temp_fd;

	lst = cmds->outfiles;
	temp_fd = -1;
	while (lst)
	{
		if (temp_fd != -1)
			close(temp_fd);
		if (((t_file *)lst->content)->append == 0)
			temp_fd = open(((t_file *)lst->content)->name,
					O_WRONLY | O_TRUNC | O_CREAT, 0664);
		else
			temp_fd = open(((t_file *)lst->content)->name,
					O_WRONLY | O_APPEND | O_CREAT, 0664);
		if (temp_fd == -1)
			mini_err(st, ERR_SUB_PRCCESS);
		lst = lst->next;
	}
	if (dup2(temp_fd, 1) == -1)
		mini_err(st, ERR_SUB_PRCCESS);
	if (temp_fd != -1)
		close(temp_fd);
	return (0);
}

int	get_outfile_fd(t_store *st, t_cmd *cmds, int num)
{
	if (num < st->size - 1)
		close(st->pip[num][0]);
	if (cmds->outfiles == NULL)
	{
		if (num == st->size - 1)
			return (0);
		if (dup2(st->pip[num][1], 1) == -1)
		{
			mini_err(st, ERR_SUB_PRCCESS);
		}
		close(st->pip[num][1]);
		return (0);
	}
	get_outfile_fd2(st, cmds);
	return (0);
}

int	find_file_by_dir(t_store *st, char **com, int e)
{
	int		i;
	char	*str;

	i = -1;
	while (++i < st->path_size)
	{
		str = strjoin_char(st->path[i], st->par[e][0], '/');
		if (!str)
		{
			free(str);
			mini_err(st, 0);
		}
		if (access(str, F_OK) == 0)
		{
			com[e] = str;
			return (1);
		}
		free(str);
	}
	return (0);
}
