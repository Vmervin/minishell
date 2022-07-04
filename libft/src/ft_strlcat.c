/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 00:58:58 by vmervin           #+#    #+#             */
/*   Updated: 2021/10/22 21:31:31 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;

	len = ft_strlen(dst);
	if (!size)
		return (ft_strlen(src));
	else if (size < len)
		return (size + ft_strlen(src));
	return (len + ft_strlcpy(dst + len, src, size - len));
}
