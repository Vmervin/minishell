/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:35:02 by vmervin           #+#    #+#             */
/*   Updated: 2022/08/03 16:36:58 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	syntax_error(int error)
{
	if (error == UNCLOSED)
		ft_putstr_fd("Error: Unclosed quotes\n", 2);
	else if (error == NEW_LINE)
	{
		ft_putstr_fd("Syntax error near unexpected token 'newline'\n", 2);
	}
	else
	{
		ft_putstr_fd("Syntax error near unexpected token '", 2);
		ft_putchar_fd(error, 2);
		ft_putstr_fd("'\n", 2);
	}
	return (error);
}

int	error_mess(char *name, int mode, char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(name, 2);
	ft_putchar_fd(' ', 2);
	if (mode == CANTOPEN)
		ft_putendl_fd(str, 2);
	if (mode == NOFILE)
	{
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	if (mode == NOEXEC)
	{
		ft_putendl_fd(str, 2);
		return (126);
	}
	return (1);
}
