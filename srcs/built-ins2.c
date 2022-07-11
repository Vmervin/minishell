/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 05:35:17 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/11 07:05:20 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int cd(t_list *lst)
{
	char *path;

	path = NULL;
	if (!lst)
		path = get_var("HOME");
	if (lst)
		path = ft_strdup(((t_file *)lst->content)->name);
	if (chdir (path) == -1)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd("No such file or directory\n", 2);
		free(path);
		return (1);
	}
	free(path);
	// com_pwd ("");
	return (0);
}
