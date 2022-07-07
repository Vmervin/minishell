/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 21:44:11 by vmervin           #+#    #+#             */
/*   Updated: 2021/11/07 17:00:04 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static	char	**ft_split_counter(char const *s, char c);
static	char	**ft_split_assignment(char const *s, char c, char **x);
static	void	ft_split_memfree(char **x, int count);
static	char	*ft_split_trim(char const *s, char c);

char	**ft_split(char const *s, char c)
{
	char	**x;
	char	*str;

	if (!s)
		return (NULL);
	str = ft_split_trim(s, c);
	x = ft_split_counter(str, c);
	if (!x)
		return (NULL);
	x = ft_split_assignment(str, c, x);
	free(str);
	return (x);
}

static	char	**ft_split_assignment(char const *s, char c, char **x)
{
	size_t	len;
	int		count;

	count = 0;
	while (s && *s)
	{
		len = 0;
		while (*s == c)
			s++;
		while (*s != c && *s != '\0')
		{
			s++;
			len++;
		}
		x[count] = ft_substr(s - len, 0, len);
		if (x[count] == NULL)
		{
			ft_split_memfree(x, count);
			return (NULL);
		}
		count++;
	}
	x[count] = NULL;
	return (x);
}

static	char	**ft_split_counter(char const *s, char c)
{
	int		count;
	char	**x;

	count = 0;
	while (s && *s != '\0')
	{
		while (*s == c)
			s++;
		while (*s != c && *s != '\0')
			s++;
		count++;
	}
	x = ft_calloc((count + 1), sizeof(char *));
	if (!x)
		return (NULL);
	return (x);
}

static	void	ft_split_memfree(char **x, int count)
{
	while (count)
	{
		free(x[count]);
		count--;
	}
	free(x[count]);
	free(x);
}

static	char	*ft_split_trim(char const *s, char c)
{
	const char	*v;
	size_t		len;

	if (!s)
		return (NULL);
	if (!c)
		return (ft_strdup(s));
	while (*s && c == *s)
		s++;
	if (!*s)
		return (ft_calloc(1, 1));
	v = s;
	len = ft_strlen(s);
	s = s + len;
	while (*s == '\0' || c == *s)
	{
		s--;
		len--;
	}
	return (ft_substr(v, 0, len + 1));
}
