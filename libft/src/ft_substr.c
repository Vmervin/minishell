/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:54:02 by vmervin           #+#    #+#             */
/*   Updated: 2021/10/26 02:01:33 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*v;
	char	*copy;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s) + 1 || !s[start])
		return (ft_calloc(1, 1));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	v = malloc(len + 1);
	if (!v)
		return (NULL);
	copy = v;
	while (len)
	{
		*v++ = s[start++];
		len--;
	}
	*v = '\0';
	return (copy);
}
