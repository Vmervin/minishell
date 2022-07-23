/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:35:17 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/23 21:56:56 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*val_search(t_token *token, char *str)
{
	char	*val;
	char	*name;
	t_list	*lst;

	lst = g_var.env;
	name = ft_substr(str, token->begin + 1, token->end - token->begin);
	if (is_strs_equal("?", name))
		val = ft_itoa(g_var.last_exec);
	else
		val = ft_strdup("");
	while (lst)
	{
		if (is_strs_equal(((t_file *)lst->content)->name, name))
		{
			free(val);
			val = ft_strdup(((t_file *)lst->content)->value);
		}
		lst = lst->next;
	}
	free(name);
	return (val);
}

char	**extract_value(t_list *lst, char *str)
{
	t_list	*tmp;
	char	**val;
	int		count;

	count = 0;
	tmp = lst;
	while (lst)
	{
		if (((t_token *)lst->content)->tokentype == '$')
			count++;
		lst = lst->next;
	}
	val = malloc(sizeof(char *) * (count + 1));
	if (!val)
		return (NULL);
	lst = tmp;
	count = 0;
	while (lst && val)
	{
		if (((t_token *)lst->content)->tokentype == '$')
			val[count++] = val_search(((t_token *)lst->content), str);
		lst = lst->next;
	}
	val[count] = NULL;
	return (val);
}

void	index_plus(t_token *expansion, t_list *tmp, size_t len)
{
	int	len2;
	int	diff;

	len2 = expansion->end - expansion->begin + 1;
	diff = len - len2;
	while (((t_token *)tmp->content)->end < expansion->begin)
		tmp = tmp->next;
	if (((t_token *)tmp->content)->begin < expansion->begin)
	{
		((t_token *)tmp->content)->end += diff;
		tmp = tmp->next;
	}
	while (tmp)
	{
		if (((t_token *)tmp->content)->tokentype != '$')
		{
			((t_token *)tmp->content)->begin += diff;
			((t_token *)tmp->content)->end += diff;
		}
		tmp = tmp->next;
	}
}

char	*expand_for_real(t_list *lst, char *str, char **val)
{
	char	*newstr;
	int		begin;
	int		end;
	t_list	*tmp;

	begin = 0;
	newstr = NULL;
	tmp = lst;
	while (lst && val && *val)
	{
		if (((t_token *)lst->content)->tokentype == '$')
		{
			end = ((t_token *)lst->content)->begin;
			newstr = ft_strjoin_free(newstr,
					ft_substr(str, begin, end - begin));
			index_plus(lst->content, tmp, ft_strlen(*val));
			newstr = ft_strjoin_free(newstr, *val++);
			begin = ((t_token *)lst->content)->end + 1;
		}
		lst = lst->next;
	}
	newstr = ft_strjoin_free(newstr, ft_substr(str, begin, ft_strlen(str)));
	free(str);
	return (newstr);
}

char	*extractor(char *string, t_parser *service)
{
	char	**val;

	val = NULL;
	val = extract_value(service->tokens, string);
	if (service->tokens && val)
		string = expand_for_real(service->tokens, string, val);
	if (val)
		free(val);
	return (string);
}
