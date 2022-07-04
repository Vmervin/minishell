/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 17:05:05 by vmervin           #+#    #+#             */
/*   Updated: 2021/10/27 21:56:09 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_strmapi_counter(char const *s);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*v;
	int		i;

	if (!s || !f)
		return (NULL);
	i = 0;
	v = ft_strmapi_counter(s);
	if (!v)
		return (NULL);
	while (*s)
	{
		*v = f(i, *s);
		i++;
		v++;
		s++;
	}
	*v = '\0';
	return (v - i);
}

static char	*ft_strmapi_counter(char const *s)
{
	size_t	len;
	char	*v;

	len = 0;
	while (*s)
	{
		len++;
		s++;
	}
	v = malloc(len + 1);
	if (!v)
		return (NULL);
	return (v);
}
