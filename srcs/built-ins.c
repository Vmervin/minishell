/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 03:49:26 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/11 07:11:33 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int echo (t_list *lst, int fd)
{
	int n;

	n = 0;
	if (is_strs_equal(((t_file *)(lst->content))->name, "-n"))
	{	
		lst = lst->next;
		n = 1;
	}
	while (lst)
	{
		ft_putstr_fd(((t_file *)(lst->content))->name, fd);		
		lst = lst->next;
	}
	if (n)
		ft_putstr_fd(((t_file *)(lst->content))->name, fd);
	else
		ft_putendl_fd(((t_file *)(lst->content))->name, fd);
	return (0);
}

int export(t_list *lst)
{
	if (!lst)
		lstprint2(g_var.env);
	return (0);
}

int env(t_list *lst)
{
	if (!lst)
		lstprint2(g_var.env);
	return (0);
}

int pwd(void)
{
	ft_printf("%s\n", getenv("PWD"));
	return (0);
}

int is_built_in(t_list *lst)
{
	if (is_strs_equal(((t_file *)(lst->content))->name, "echo"))
		return (echo(lst->next, 0));
	if (is_strs_equal(((t_file *)(lst->content))->name, "export"))
		return(export(lst->next));
	if (is_strs_equal(((t_file *)(lst->content))->name, "env"))
		return(env(lst->next));
	if (is_strs_equal(((t_file *)(lst->content))->name, "unset"))
		return(0);
	if (is_strs_equal(((t_file *)(lst->content))->name, "pwd"))
		return(pwd());
	if (is_strs_equal(((t_file *)(lst->content))->name, "cd"))
		return(cd(lst->next));
	return (1);
}
