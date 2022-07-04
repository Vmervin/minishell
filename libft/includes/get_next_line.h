/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:20:00 by vmervin           #+#    #+#             */
/*   Updated: 2022/01/23 21:18:14 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
//# include <stdlib.h>
//# include <unistd.h>

//char		*get_next_line(int fd);
//static char	*read_line(int fd, char *v, ssize_t *i, char *g);
//static void	ft_bzero_gnl(char *v, ssize_t x);
//char		*buffer_end_of_file(char *v, ssize_t *i, char *g);
//char		*buffer_new_line(char *v, ssize_t *i, char *g);
char	*ft_strjoin_gnl(char const *s1, char const *s2, size_t x, size_t len1);
char	*ft_strdup_gnl(const char *s);
size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t size);
ssize_t	ft_memchr_gnl(const char *s, int c, ssize_t n);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 80
# endif

#endif