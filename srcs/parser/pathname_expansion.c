/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:35:37 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/07 13:50:56 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*remove_quotes(t_list *lst, char *str)
{
	char	*newstr;
	int		begin;
	int		end;

	begin = 0;
	newstr = NULL;
	if (!lst)
		return (str);
	while (lst)
	{
		if (((t_token *)lst->content)->tokentype != '$')
		{
			end = ((t_token *)lst->content)->begin;
			newstr = ft_strjoin_free(newstr,
					ft_substr(str, begin, end - begin));
			begin = end + 1;
			end = ((t_token *)lst->content)->end;
			newstr = ft_strjoin_free(newstr,
					ft_substr(str, begin, end - begin));
			begin = ((t_token *)lst->content)->end + 1;
		}
		lst = lst->next;
	}
	if (ft_strlen(str) > begin)
		newstr = ft_strjoin_free(newstr, ft_substr(str, begin,
					ft_strlen(str) - begin));
	free(str);
	return (newstr);
}

char	*expand(char *string)
{
	t_list	*tokens;
	char	**val;
	int		i;

	i = 0;
	tokens = NULL;
	val = NULL;
	if (ft_strchr(string, '$') || ft_strchr(string, '\'')
		|| ft_strchr(string, '\"'))
	{
		quote_token_search(&tokens, '\"', string);
		dollar_sign_token_search(&tokens, '$', string);
		ft_list_sort(&tokens, compare_tokens);
		val = extract_value(tokens, string);
		if (tokens && val)
			string = expand_for_real(tokens, string, val);
		string = remove_quotes(tokens, string);
		ft_lstclear(&tokens, free);
		if (val)
			free(val);
	}
	return (string);
}

void	parse_word(t_list *lst, int vars)
{
	while (lst)
	{
		if (vars)
		{
			((t_file *)(lst->content))->value
				= expand(((t_file *)(lst->content))->value);
		}
		else
			((t_file *)(lst->content))->name
				= expand(((t_file *)(lst->content))->name);
		lst = lst->next;
	}
}
