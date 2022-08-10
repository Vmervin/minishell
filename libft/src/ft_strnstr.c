/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 15:52:46 by vmervin           #+#    #+#             */
/*   Updated: 2021/11/07 18:53:02 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*v;
	char	*b;
	ssize_t	lenbig;
	ssize_t	lenlittle;

	b = (char *) big;
	v = (char *) big;
	lenbig = ft_strlen(big);
	lenlittle = ft_strlen(little);
	if (!lenlittle)
		return (b);
	while (len && lenbig >= lenlittle)
	{
		v = ft_strchr(b, *little);
		if ((v && (unsigned long)(v - big) <= len - lenlittle
			&& !ft_strncmp(v, little, lenlittle)) || !v)
			return (v);
		lenbig = lenbig - (v - b) - 1;
		b = v + 1;
	}
	return (NULL);
}
