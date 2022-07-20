/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 18:20:37 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/19 22:22:40 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	var_free(t_list *lst)
{
	if (!lst)
		return ;
	if (((t_file *)(lst->content))->name)
		free(((t_file *)(lst->content))->name);
	if (((t_file *)(lst->content))->value)
		free(((t_file *)(lst->content))->value);
	ft_lstdelone(lst, free);
}

void	change_vars(char *name, char *val)
{
	t_list	*lst;

	if (!val)
		return ;
	lst = g_var.env;
	while (lst)
	{
		if (is_strs_equal(((t_file *)lst->content)->name, name))
		{
			free(((t_file *)lst->content)->value);
			// free(name);
			((t_file *)lst->content)->value = val;
			return ;
		}
		lst = lst->next;
	}
	add_list_file(&g_var.env, 0, name, val);
}

void	add_vars(t_list *lst, int ex)
{
	char	*name;
	char	*val;

	while (lst)
	{
		if (((t_file *)(lst->content))->append == ex)
		{
			name = ft_strdup(((t_file *)(lst->content))->name);
			val = ft_strdup(((t_file *)(lst->content))->value);
			change_vars(name, val);
			lst = lst->next;
		}
	}
	ft_list_sort(&g_var.env, compare_names);
}

void	unset_vars(t_list *lst)
{
	if (lst && g_var.env)
	{
		while (!delete_node(&g_var.env, ((t_file *)(lst->content))->name))
			;
	}
}

void	var_process(t_cmd *simplcmds)
{
	if (!simplcmds[1].empty)
		return ;
	if (!simplcmds[0].command)
	{
		add_vars(simplcmds[0].vars, 0);
		return ;
	}
	else if (is_strs_equal(((t_file *)(simplcmds[0].command->content))->name,
		"export"))
	{
		if (!simplcmds[0].command->next)
			return ;
		add_vars(simplcmds[0].command, 0);
		add_vars(simplcmds[0].vars, 1);
	}
	else if (is_strs_equal(((t_file *)(simplcmds[0].command->content))->name,
		"unset"))
		unset_vars(simplcmds[0].command);
	else
		return ;
}
