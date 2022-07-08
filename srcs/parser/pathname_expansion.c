/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:35:37 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/08 03:40:18 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*skip_quote(char *newstr, char *str, int *tmp, t_token *tok)
{
	int	end;
	int	begin;

	begin = *tmp;
	end = tok->begin;
	newstr = ft_strjoin_free(newstr, ft_substr(str, begin, end - begin));
	begin = end + 1;
	end = tok->end;
	newstr = ft_strjoin_free(newstr, ft_substr(str, begin, end - begin));
	begin = tok->end + 1;
	*tmp = begin;
	return (newstr);
}

char	*remove_quotes(t_list *lst, char *str)
{
	char	*newstr;
	int		begin;

	begin = 0;
	newstr = NULL;
	if (!lst)
		return (str);
	while (lst)
	{
		if (((t_token *)lst->content)->tokentype != '$')
			newstr = skip_quote(newstr, str, &begin,
					((t_token *)lst->content));
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
	t_parser	service;
	char		**val;
	int			i;

	i = 0;
	service.tokens = NULL;
	service.string = string;
	service.error = 0;
	val = NULL;
	if (ft_strchr(string, '$') || ft_strchr(string, '\'')
		|| ft_strchr(string, '\"'))
	{
		quote_token_search(&service);
		dollar_sign_token_search(&service.tokens, '$', string);
		ft_list_sort(&service.tokens, compare_tokens);
		val = extract_value(service.tokens, string);
		if (service.tokens && val)
			string = expand_for_real(service.tokens, string, val);
		string = remove_quotes(service.tokens, string);
		ft_lstclear(&service.tokens, free);
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
