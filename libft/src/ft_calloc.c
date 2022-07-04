/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 01:40:37 by vmervin           #+#    #+#             */
/*   Updated: 2022/01/23 00:53:56 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*v;

	if (size && nmemb > (__SIZE_MAX__ / size))
		return (NULL);
	v = malloc(nmemb * size);
	if (!v)
		return (NULL);
	else
		return (ft_memset(v, '\0', (nmemb * size)));
}
