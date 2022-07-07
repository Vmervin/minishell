/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:35:31 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/07 13:46:43 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_list(t_list **lst, int begin, int end, char type)
{
	t_token	*content;

	content = malloc(sizeof(t_token));
	content->begin = begin;
	content->end = end;
	content->tokentype = (int)type;
	ft_lstadd_back(lst, ft_lstnew(content));
}

void	quote_token_search(t_list **lst, char type, char *str)
{
	int	i;
	int	len;
	int	quotes[2];

	i = 0;
	len = ft_strlen(str);
	quotes[0] = '\'';
	quotes[1] = '\"';
	while (i < len)
	{
		if (!ft_strchr(str, '\'') && ft_strchr(str, '\"'))
			i = quote_search(lst, i, '\"', str);
		else if (ft_strchr(str, '\'') && !ft_strchr(str, '\"'))
			i = quote_search(lst, i, '\'', str);
		else
		{
			i = quote_search(lst, i, quotes[!(ft_strchr(str, '\'')
						< ft_strchr(str, '\"'))], str);
			i = quote_search(lst, i, quotes[(ft_strchr(str, '\'')
						< ft_strchr(str, '\"'))], str);
		}
	}
}

size_t	quote_search(t_list **lst, int i, char type, char *str)
{
	int	tmp_begin;

	tmp_begin = -1;
	while (str[i] && str[i] != type)
		i++;
	if (!str[i])
		return (i);
	if (str[i] && str[i] == type)
		tmp_begin = i;
	i++;
	while (str[i] && str[i] != type)
		i++;
	if (str[i] && str[i] == type && tmp_begin >= 0)
		add_list(lst, tmp_begin, i, type);
	if (tmp_begin > 0 && !str[i])
		syntax_error(1);
	return (++i);
}
