/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 07:29:37 by vmervin           #+#    #+#             */
/*   Updated: 2022/01/31 00:12:13 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "../includes/ft_printf.h"

int	ft_putchar_printf(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr_printf(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (ft_putstr_printf("(null)"));
	while (i < ft_strlen(s))
	{
		ft_putchar_printf(s[i]);
		i++;
	}
	return (i);
}
