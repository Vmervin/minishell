/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:19:53 by vmervin           #+#    #+#             */
/*   Updated: 2022/01/23 21:18:43 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "../includes/get_next_line.h"

static char	*read_line(int fd, char *v, ssize_t *i, char *g);
static void	ft_bzero_gnl(char *v, ssize_t x);
static char	*buffer_end_of_file(char *v, ssize_t *i, char *g);
static char	*buffer_new_line(char *v, ssize_t *i, char *g);

char	*get_next_line(int fd)
{
	static char		v[BUFFER_SIZE];
	char			*g;
	static ssize_t	i;

	g = ft_strdup_gnl("");
	if (!g)
		return (NULL);
	if (i >= 0 && v[i] == '\n')
	{
		g = buffer_new_line(v, &i, g);
		if (i != -2 || !g)
			return (g);
	}
	return (read_line(fd, v, &i, g));
}

char	*buffer_new_line(char *v, ssize_t *i, char *g)
{
	ssize_t	j;
	ssize_t	x;
	ssize_t	var;

	j = *i + 1;
	x = BUFFER_SIZE - j;
	var = ft_memchr_gnl(v + j, '\n', x);
	if (var >= 0)
	{
		g = ft_strjoin_gnl(g, v + j, var + 1, 0);
		*i = var + j;
		return (g);
	}
	return (buffer_end_of_file(v, i, g));
}

/*char	*buffer_end_of_file(char *v, ssize_t *i, char *g)
{
	ssize_t	j;
	ssize_t	x;
	ssize_t	var;

	j = *i + 1;
	x = BUFFER_SIZE - j;
	var = ft_memchr_gnl(v + j, '\0', x);
	if (var > 0)
	{
		*i = -1;
//		g = ft_strjoin_gnl;
//		ft_bzero(v, 0);
		return (ft_strjoin_gnl(g, v + j, var + 1, 0));
	}
	if (var == 0)
	{
		ft_bzero_gnl(v, 0);
		return (ft_strjoin_gnl(g, NULL, 0, 0));
	}
	*i = -2;
	return (ft_strjoin_gnl(g, v + j, x, 0));
}*/

char	*buffer_end_of_file(char *v, ssize_t *i, char *g)
{
	ssize_t	j;
	ssize_t	x;
	ssize_t	var;

	j = *i + 1;
	x = BUFFER_SIZE - j;
	var = ft_memchr_gnl(v + j, '\0', x);
	if (var > 0)
	{
		*i = -1;
		g = ft_strjoin_gnl(g, v + j, var + 1, 0);
	}
	else if (var == 0)
		g = ft_strjoin_gnl(g, NULL, 0, 0);
	else
	{
		*i = -2;
		g = ft_strjoin_gnl(g, v + j, x, 0);
	}
	ft_bzero_gnl(v, 0);
	return (g);
}

char	*read_line(int fd, char *v, ssize_t *i, char *g)
{
	ssize_t	x;
	size_t	len;

	if (read(fd, NULL, 0) < 0 || !g)
		return (ft_strjoin_gnl(g, NULL, 0, 0));
	x = read(fd, v, BUFFER_SIZE);
	if (x == 0 && *g == '\0')
		return (ft_strjoin_gnl(g, NULL, 0, 0));
	ft_bzero_gnl(v, x);
	len = ft_strlen(g);
	while (x)
	{
		*i = ft_memchr_gnl(v, '\n', x);
		if (*i >= 0)
			return (ft_strjoin_gnl(g, v, *i + 1, len));
		g = ft_strjoin_gnl(g, v, x, len);
		len = len + x;
		x = read(fd, v, BUFFER_SIZE);
		ft_bzero_gnl(v, x);
	}
	return (g);
}

void	ft_bzero_gnl(char *v, ssize_t x)
{
	ssize_t	count;

	count = 0;
	while (x + count < BUFFER_SIZE)
	{
		v[x + count++] = '\0';
	}
}
