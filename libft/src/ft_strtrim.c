/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 05:16:53 by vmervin           #+#    #+#             */
/*   Updated: 2021/11/01 02:19:16 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strtrim(char const *s, char const *set)
{
	const char	*v;
	const char	*s2;
	size_t		len;

	if (!s)
		return (NULL);
	if (!set || !*set)
		return (ft_strdup(s));
	while (*s && ft_strchr(set, *s))
		s++;
	if (!*s)
		return (ft_calloc(1, 1));
	v = s;
	len = ft_strlen(s);
	s2 = s + len;
	while (ft_strchr(set, *s2))
	{
		s2--;
		len--;
	}
	return (ft_substr(v, 0, len + 1));
}
