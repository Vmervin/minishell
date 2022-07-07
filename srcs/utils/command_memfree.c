/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_memfree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:35:08 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/07 13:35:09 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	memfree(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (((t_file *)(tmp->content))->name)
			free(((t_file *)(tmp->content))->name);
		if (((t_file *)(tmp->content))->value)
			free(((t_file *)(tmp->content))->value);
		tmp = tmp->next;
	}
	ft_lstclear(&lst, free);
}

void	command_memfree(t_cmd *simplcmds)
{
	int	i;

	i = 0;
	if (!simplcmds)
		return ;
	while (!simplcmds[i].empty)
	{
		memfree(simplcmds[i].infiles);
		memfree(simplcmds[i].outfiles);
		memfree(simplcmds[i].vars);
		memfree(simplcmds[i].command);
		i++;
	}
	free(simplcmds);
}
