/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_empty.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 06:39:04 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/12 18:30:27 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	delete_node(t_list **head, char *key)
{
	t_list	*temp;
	t_list	*prev;

	temp = *head;
	prev = *head;
	if (temp != NULL && is_strs_equal(((t_file *)temp->content)->name, key))
	{
		*head = temp->next;
		var_free(temp);
		return (0);
	}
	while (temp != NULL && !is_strs_equal(((t_file *)temp->content)->name, key))
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return (1);
	prev->next = temp->next;
	var_free(temp);
	return (0);
}

void	remove_empty(t_cmd *cmd, int *error)
{
	if (!cmd)
		return ;
	while (!delete_node(&cmd->command, ""))
		;
	*error = !delete_node(&cmd->infiles, "");
	if (*error)
	{
		ft_putstr_fd("Error, undefined redirection input\n", 2);
		return ;
	}
	*error = !delete_node(&cmd->outfiles, "");
	if (*error)
		ft_putstr_fd("Error, undefined redirection output\n", 2);
}
