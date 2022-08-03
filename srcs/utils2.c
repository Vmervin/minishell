/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 18:13:17 by vmervin           #+#    #+#             */
/*   Updated: 2022/08/03 16:50:08 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	compare_names(void *content1, void *content2)
{
	return (ft_strncmp(((t_file *)content1)->name,
			((t_file *)content2)->name,
			ft_strlen(((t_file *)content1)->name)));
}

int	is_strs_equal(char *str1, char *str2)
{
	return (!ft_strncmp(str1, str2, ft_strlen(str1))
		&& (ft_strlen(str1) == ft_strlen(str2)));
}

char	*ft_strjoin_free(const char *s1, const char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (s1)
		free((char *)s1);
	if (s2)
		free((char *)s2);
	return (res);
}

void	add_list(t_list **lst, int begin, int end, char type)
{
	t_token	*content;

	content = malloc(sizeof(t_token));
	if (!content)
		return ;
	content->begin = begin;
	content->end = end;
	content->tokentype = (int)type;
	ft_lstadd_back(lst, ft_lstnew(content));
}

int	add_list_file(t_list **lst, int append, char *name, char *value)
{
	t_file	*content;

	content = malloc(sizeof(t_file));
	if (!content)
	{
		if (name)
			free (name);
		if (value)
			free (value);
		return (ERR_MALLOC);
	}
	content->append = append;
	content->name = name;
	content->value = value;
	ft_lstadd_back(lst, ft_lstnew(content));
	return (0);
}
