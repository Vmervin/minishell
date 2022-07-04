/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:59:36 by vmervin           #+#    #+#             */
/*   Updated: 2021/11/07 16:26:16 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int	i;

	i = n;
	if (!dest && !src)
		return (NULL);
	if (!src)
		return (dest);
	while (n)
	{
		ft_memset(dest, *(char *)src, 1);
		dest++;
		src++;
		n = (n - sizeof(char));
	}
	return (dest - i);
}
