/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:34:53 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/11 04:01:32 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	compare_tokens(void *content1, void *content2)
{
	return (((t_token *)content1)->begin > ((t_token *)content2)->begin);
}

void	ft_swap_data(t_list *a, t_list *b)
{
	t_list	tmp;

	tmp.content = a->content;
	a->content = b->content;
	b->content = tmp.content;
}

void	ft_list_sort(t_list **begin_list, int (*cmp)())
{
	t_list	*current;

	if (*begin_list && (*begin_list)->content)
	{
		current = *begin_list;
		while (current->next)
		{
			if ((*cmp)(current->content, current->next->content) > 0)
			{
				ft_swap_data(current, current->next);
				current = *begin_list;
			}
			else
				current = current->next;
		}
	}
}

void	lstprint(t_list *lst)
{
	while (lst->next)
	{
		ft_printf("list= %d ", ((t_token *)lst->content)->begin);
		ft_printf("%d ", ((t_token *)lst->content)->end);
		ft_printf("%c\n", ((t_token *)lst->content)->tokentype);
		lst = lst->next;
	}
	ft_printf("list = %d ", ((t_token *)lst->content)->begin);
	ft_printf("%d ", ((t_token *)lst->content)->end);
	ft_printf("%c\n", ((t_token *)lst->content)->tokentype);
}

void	lstprint2(t_list *lst)
{
	if (!lst)
		return ;
	while (lst->next)
	{
		ft_printf("%s=", ((t_file *)lst->content)->name);
		ft_printf("%s\n", ((t_file *)lst->content)->value);
		lst = lst->next;
	}
	ft_printf("%s=", ((t_file *)lst->content)->name);
	ft_printf("%s\n", ((t_file *)lst->content)->value);
}
