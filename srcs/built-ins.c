/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 03:49:26 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/22 22:35:34 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	echo(t_list *lst, int fd)
{
	int	n;

	n = 0;
	if (!lst)
		return (0);
	if (is_strs_equal(((t_file *)(lst->content))->name, "-n"))
	{	
		lst = lst->next;
		n = 1;
	}
	while (lst)
	{
		if (!lst->next && !n)
			ft_putendl_fd(((t_file *)(lst->content))->name, fd);
		else
		{
			ft_putstr_fd(((t_file *)(lst->content))->name, fd);
			ft_putchar_fd(' ', fd);
		}
		lst = lst->next;
	}
	return (0);
}

int	export(t_list *lst)
{
	if (!lst)
		lstprint2(g_var.env);
	return (0);
}

int	env(t_list *lst)
{
	if (!lst)
		lstprint2(g_var.env);
	return (0);
}

int	pwd(void)
{
	char	*s;

	s = getcwd(NULL, 0);
	if (!s)
	{
		ft_putstr_fd("Error getting pwd\n", 2);
		return (1);
	}
	ft_printf("%s\n", s);
	return (0);
}

int	is_built_in(t_list *lst, int i, t_info *info)
{
	if (!lst)
		return (1);
	if (is_strs_equal(((t_file *)(lst->content))->name, "echo"))
		return (echo(lst->next, 1));
	if (is_strs_equal(((t_file *)(lst->content))->name, "export"))
		return (export(lst->next));
	if (is_strs_equal(((t_file *)(lst->content))->name, "env"))
		return (env(lst->next));
	if (is_strs_equal(((t_file *)(lst->content))->name, "unset"))
		return (0);
	if (is_strs_equal(((t_file *)(lst->content))->name, "pwd"))
		return (pwd());
	if (is_strs_equal(((t_file *)(lst->content))->name, "cd") && i)
		return (cd(lst->next));
	if (is_strs_equal(((t_file *)(lst->content))->name, "exit") && i)
		return (exit_shell(info));
	return (1);
}
