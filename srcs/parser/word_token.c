/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:35:12 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/31 19:46:17 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_token(t_list *lst, int i, char type)
{
	while (lst)
	{
		if (i >= ((t_token *)lst->content)->begin
			&& i <= ((t_token *)lst->content)->end)
		{
			if (type != '$')
				return (1);
			else
			{
				if (((t_token *)lst->content)->tokentype != '\"')
					return (2);
			}
		}
		lst = lst->next;
	}
	return (0);
}

static size_t	word_search(t_list **lst, int i, char *str)
{
	int	tmp_begin;

	tmp_begin = -1;
	if (!str[i])
		return (++i);
	while (str[i] && !is_token(*lst, i, 0))
	{
		if (tmp_begin < 0)
			tmp_begin = i;
		i++;
	}
	i--;
	if (i >= 0 && str[i] && tmp_begin >= 0)
		add_list(lst, tmp_begin, i, 'w');
	return (i += 2);
}

void	word_token_search(t_list **lst, char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (i >= 0 && i <= len)
		i = word_search(lst, i, str);
}
