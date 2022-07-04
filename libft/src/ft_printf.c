/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 07:29:31 by vmervin           #+#    #+#             */
/*   Updated: 2022/01/31 00:12:04 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "../includes/ft_printf.h"

static int	ft_putnbr_printf(int n, int x);
static int	ft_putnbrhex_printf(unsigned int n, char x);
static int	ft_putpointer(size_t n, int x);
static int	ft_superfunc_printf(va_list ap, const char *format);

int	ft_printf(const char *format, ...)
{
	int		i;
	va_list	ap;
	int		res;

	i = 0;
	res = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] != '%')
			res += ft_putchar_printf(format[i]);
		else
		{
			if (ft_strchr("cdipsuxX%", format[i + 1]))
			{
				i++;
				res += ft_superfunc_printf(ap, format + i);
			}
		}
		i++;
	}
	va_end(ap);
	return (res);
}

int	ft_superfunc_printf(va_list ap, const char *format)
{
	if (*format == 'c')
		return (ft_putchar_printf(va_arg(ap, int)));
	else if (*format == 'd' || *format == 'i')
		return (ft_putnbr_printf(va_arg(ap, int), 1));
	else if (*format == 'u')
		return (ft_putnbr_printf(va_arg(ap, unsigned int), 0));
	else if (*format == 's')
		return (ft_putstr_printf(va_arg(ap, char *)));
	else if (*format == 'x' || *format == 'X')
		return (ft_putnbrhex_printf(va_arg(ap, unsigned int), *format));
	else if (*format == 'p')
		return (ft_putpointer(va_arg(ap, size_t), 1));
	else
		return (ft_putchar_printf('%'));
}

int	ft_putnbr_printf(int n, int x)
{
	int	i;

	i = 0;
	if (n < 0 && x)
	{
		i += ft_putchar_printf('-');
		if (n / 10)
			i += ft_putnbr_printf(-(n / 10), 0);
		i += ft_putchar_printf(-(n % 10) + '0');
	}
	else if (n >= 0 && n < 10)
		i += ft_putchar_printf(n + '0');
	else
	{
		i += ft_putnbr_printf((unsigned int)n / 10, 0);
		i += ft_putchar_printf((unsigned int)n % 10 + '0');
	}
	return (i);
}

int	ft_putnbrhex_printf(unsigned int n, char x)
{
	int	i;

	i = 0;
	if (n < 10)
		i += ft_putchar_printf(n + '0');
	else if (n >= 10 && n < 16)
		i += ft_putchar_printf(n - 10 + x - 23);
	else
	{
		i += ft_putnbrhex_printf(n / 16, x);
		if (n % 16 < 10)
			i += ft_putchar_printf(n % 16 + '0');
		else
			i += ft_putchar_printf(n % 16 + x - 23 - 10);
	}
	return (i);
}

int	ft_putpointer(size_t n, int x)
{
	int	i;

	i = 0;
	if (x)
		i += ft_putstr_printf("0x");
	if (n < 10)
		i += ft_putchar_printf(n + '0');
	else if (n >= 10 && n < 16)
		i += ft_putchar_printf(n - 10 + 'a');
	else
	{
		i += ft_putpointer(n / 16, 0);
		if (n % 16 < 10)
			i += ft_putchar_printf(n % 16 + '0');
		else
			i += ft_putchar_printf(n % 16 + 'a' - 10);
	}
	return (i);
}
