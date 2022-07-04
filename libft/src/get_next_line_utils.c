/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:19:45 by vmervin           #+#    #+#             */
/*   Updated: 2022/01/23 21:57:15 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "../includes/get_next_line.h"

char	*ft_strjoin_gnl(char const *s1, char const *s2, size_t x, size_t len1)
{
	char	*v;

	if (!s1)
		return (NULL);
	if (!s2)
	{
		free((char *)s1);
		return (NULL);
	}
	v = malloc(len1 + x + 1);
	if (!v)
		return (NULL);
	ft_strlcpy_gnl(v, s1, len1 + 1);
	ft_strlcpy_gnl(v + len1, s2, x + 1);
	free((char *)s1);
	return (v);
}

size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t size)
{
	while (--size)
	{
		*dst++ = *src++;
	}
	*dst = '\0';
	return (size);
}

ssize_t	ft_memchr_gnl(const char *s, int c, ssize_t n)
{
	ssize_t	i;

	i = 0;
	while (n > 0)
	{
		if (s[i] == (unsigned char)c)
			return (i);
		i++;
		n--;
	}
	return (-1);
}

char	*ft_strdup_gnl(const char *s)
{
	char	*v;

	v = malloc(1);
	if (!v)
		return (NULL);
	ft_strlcpy_gnl(v, s, 1);
	return (v);
}
