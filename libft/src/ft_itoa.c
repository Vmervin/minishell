/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 05:40:38 by vmervin           #+#    #+#             */
/*   Updated: 2021/11/07 16:03:15 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_itoa_counter(int n, size_t len);
static char	*ft_itoa_counter_minus(int n, size_t len);
static char	*ft_itoa_exceptions(void);

char	*ft_itoa(int n)
{
	int		x;
	size_t	len;
	char	*num;

	if (n == 0)
	{
		num = ft_itoa_exceptions();
		return (num);
	}
	x = n;
	len = 0;
	while (x)
	{
		x = x / 10;
		len++;
	}
	if (n < 0)
		num = ft_itoa_counter_minus(n, len);
	else
		num = ft_itoa_counter(n, len);
	return (num);
}

static char	*ft_itoa_counter(int n, size_t len)
{
	char	*num;
	char	*buf;

	num = malloc(len + 1);
	if (!num)
		return (NULL);
	buf = num + len;
	*buf = '\0';
	buf--;
	while (len)
	{
		*buf = n % 10 + '0';
		n = n / 10;
		len--;
		buf--;
	}
	return (num);
}

static char	*ft_itoa_counter_minus(int n, size_t len)
{
	char	*num;
	char	*buf;

	num = malloc(len + 2);
	if (!num)
		return (NULL);
	buf = num + len + 1;
	*buf = '\0';
	buf--;
	while (len)
	{
		*buf = -(n % 10) + '0';
		n = n / 10;
		len--;
		buf--;
	}
	*buf = '-';
	return (num);
}

static char	*ft_itoa_exceptions(void)
{
	char	*num;

	num = malloc(2);
	if (!num)
		return (NULL);
	num = ft_memcpy(num, "0", 2);
	return (num);
}
