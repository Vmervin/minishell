/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:49:42 by vmervin           #+#    #+#             */
/*   Updated: 2022/08/03 16:35:50 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	open_in(t_cmd cmd, t_info *info)
{
	t_list	*lst;

	lst = cmd.infiles;
	if (!lst)
		return (1);
	info->fdin = -1;
	while (lst)
	{
		if (((t_file *)(lst->content))->append)
			heredoc_proc(lst, info);
		else
			info->fdin = open(((t_file *)(lst->content))->name, O_RDONLY);
		if (info->fdin < 0)
		{
			info->res = error_mess(((t_file *)(lst->content))->name, CANTOPEN,
					strerror(errno));
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

static int	open_out(t_cmd cmd, t_info *info)
{
	t_list	*lst;

	lst = cmd.outfiles;
	if (!lst)
		return (1);
	info->fdout = -1;
	while (lst)
	{
		if (((t_file *)(lst->content))->append)
			info->fdout = open(((t_file *)(lst->content))->name,
					O_WRONLY | O_CREAT | O_APPEND, 0664);
		else
			info->fdout = open(((t_file *)(lst->content))->name,
					O_WRONLY | O_CREAT | O_TRUNC, 0664);
		if (info->fdout < 0)
		{
			info->res = error_mess(((t_file *)(lst->content))->name, CANTOPEN,
					strerror(errno));
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

int	open_loop(t_cmd cmd, t_info *info)
{
	if (!open_in(cmd, info))
	{
		dup2(info->fdin, 0);
		close(info->fdin);
	}
	if (!open_out(cmd, info))
	{
		dup2(info->fdout, 1);
		close(info->fdout);
	}
	return (0);
}
