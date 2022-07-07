/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:35:02 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/07 13:35:03 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	syntax_error(int error)
{
	if (error == 1)
		ft_putstr_fd("Error: Unclosed quotes\n", 2);
	else
	{
		ft_putstr_fd("Syntax error near unexpected token '", 2);
		ft_putchar_fd(error, 2);
		ft_putstr_fd("'\n", 2);
	}
	g_var.error = error;
	return (error);
}
