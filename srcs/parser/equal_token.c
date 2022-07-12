/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:35:48 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/12 00:25:35 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	equal_token_search(t_list **lst, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			is_word(*lst, i, str);
		i++;
	}
}

void	is_word(t_list *lst, int i, char *str)
{
	while (lst)
	{
		if (i >= ((t_token *)lst->content)->begin
			&& i <= ((t_token *)lst->content)->end)
		{
			if (((t_token *)lst->content)->tokentype == 'w')
			{
				if (((t_token *)lst->content)->begin != i
					&& is_name(((t_token *)lst->content), i, str))
				{
					((t_token *)lst->content)->tokentype = '=';
					((t_token *)lst->content)->end = i;
				}
			}
		}
		lst = lst->next;
	}
}

int	is_name(t_token *token, int i, char *str)
{
	int	j;

	j = token->begin;
	if (!ft_isalpha(str[j]) && str[j] != '_')
		return (0);
	while (j < i)
	{
		if (!ft_isalnum(str[j]) && str[j] != '_')
			return (0);
		j++;
	}
	return (1);
}
