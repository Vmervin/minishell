/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 18:48:04 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/09 18:48:05 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_name(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		i++;
	}
	return (ft_substr(str, 0, i));
}

void	env_to_list(char **env)
{
	char	*val;
	char	*name;
	int		i;

	i = 0;
	while (env[i])
	{
		name = get_name(env[i]);
		val = ft_substr(ft_strchr(env[i], '='), 1, ft_strlen(env[i]));
		add_list_file(&g_var.env, 0, name, val);
		i++;
	}
}

char	*get_var(char *name)
{
	t_list	*lst;

	lst = g_var.env;
	while (lst)
	{
		if (is_strs_equal(((t_file *)lst->content)->name, name))
		{
			if (((t_file *)lst->content)->value)
				return (ft_strdup(((t_file *)lst->content)->value));
		}
		lst = lst->next;
	}
	return (NULL);
}

void	remove_vars(char *name)
{
	t_list *lst;
	t_list *tmp;

	lst = g_var.env;
	if (is_strs_equal(((t_file *)lst->content)->name, name))
	{
		g_var.env = lst->next;
		var_free(lst);
		return ;
	}
	tmp = lst;
	lst = lst->next;
	while (lst)
	{
		if (is_strs_equal(((t_file *)lst->content)->name, name))
		{
			tmp->next = lst->next;
			var_free(lst);
			return ;		
		}
		tmp = lst;
		lst = lst->next;
	}
}
