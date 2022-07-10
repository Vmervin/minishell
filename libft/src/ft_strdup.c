/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:23:36 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/10 05:18:26 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s)
{
	char	*v;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	v = malloc(len + 1);
	if (!v)
		return (NULL);
	ft_strlcpy(v, s, len + 1);
	return (v);
}
