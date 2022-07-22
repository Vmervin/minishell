/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_redirect_token.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:35:25 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/22 23:33:51 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_quoted_word(t_list *lst, int i, char type)
{
	while (lst)
	{
		if (type != '$' && ((t_token *)lst->content)->tokentype == '\"')
		{
			if (i >= ((t_token *)lst->content)->begin
				&& i <= ((t_token *)lst->content)->end)
				return (2);
		}
		if (((t_token *)lst->content)->tokentype == '\'')
		{
			if (i >= ((t_token *)lst->content)->begin
				&& i <= ((t_token *)lst->content)->end)
				return (1);
		}
		lst = lst->next;
	}
	return (0);
}

void	one_simbol_token_search(t_list **lst, char type, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == type && !is_quoted_word(*lst, i, type))
			add_list(lst, i, i, type);
		i++;
	}
}

size_t	many_simbol_search(t_list **lst, int i, char *type, char *str)
{
	int	tmp_begin;

	tmp_begin = -1;
	if (!str[i])
		return (++i);
	while (str[i] && !ft_strchr(type, str[i]))
		i++;
	while (str[i] && ft_strchr(type, str[i])
		&& !is_quoted_word(*lst, i, type[0]))
	{
		if (tmp_begin < 0)
			tmp_begin = i;
		i++;
	}
	i--;
	if (str[i] && tmp_begin >= 0)
		add_list(lst, tmp_begin, i, ' ');
	return (i += 2);
}

void	space_token_search(t_list **lst, char *type, char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (i <= len)
		i = many_simbol_search(lst, i, type, str);
}
