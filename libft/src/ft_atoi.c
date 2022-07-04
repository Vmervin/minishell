/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 22:39:27 by vmervin           #+#    #+#             */
/*   Updated: 2022/01/23 00:53:52 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	collectnumbers(const char *nptr);
static int	ft_isspace(int i);

int	ft_atoi(const char *nptr)
{
	int	n;

	n = 1;
	if (nptr)
	{
		while (ft_isspace(*nptr))
			nptr++;
		if (*nptr == '+')
		{
			nptr++;
			return (collectnumbers(nptr) * n);
		}
		else if (*nptr == '-')
		{
			nptr++;
			n = -n;
			return (collectnumbers(nptr) * n);
		}
		else
			return (collectnumbers(nptr) * n);
	}
	return (0);
}

static int	collectnumbers(const char *nptr)
{
	int	y;

	y = 0;
	while (ft_isdigit(*nptr))
	{
		y = (y * 10) + (*nptr - '0');
		nptr++;
	}
	return (y);
}

static int	ft_isspace(int i)
{
	unsigned char	c;

	c = i;
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	else
		return (0);
}
