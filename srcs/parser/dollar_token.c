/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:35:53 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/23 00:35:40 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	dollar_sign_search(t_list **lst, int i, char type, char *str)
{
	int	tmp_begin;

	tmp_begin = -1;
	while (str[i] && str[i] != '$')
		i++;
	if (!str[i])
		return (i);
	if (str[i] == '$' && !is_quoted_word(*lst, i, type))
		tmp_begin = i;
	i++;
	if (str[i] == '?' && tmp_begin >= 0)
		add_list(lst, tmp_begin, i, '$');
	if (!str[i] || !(ft_isalpha(str[i]) || str[i] == '_'))
		return (i);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	i--;
	if (str[i] && tmp_begin >= 0)
		add_list(lst, tmp_begin, i, '$');
	return (++i);
}

void	dollar_sign_token_search(t_list **lst, char type, char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
		i = dollar_sign_search(lst, i, type, str);
}
