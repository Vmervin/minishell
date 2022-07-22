/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:35:02 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/22 21:52:28 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	syntax_error(int error)
{
	if (error == 1)
		ft_putstr_fd("Error: Unclosed quotes\n", 2);
	else if (!error)
	{
		ft_putstr_fd("Syntax error near unexpected token 'newline'\n", 2);
		return (999);
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
	if (mode == 1)
		ft_putendl_fd(str, 2);
		// ft_putstr_fd(": No such file or directory\n", 2);
	if (mode == 2)
		ft_putendl_fd(str, 2);
		// ft_putstr_fd(": Access denied\n", 2);
	if (mode == 3)
	{
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	if (mode == 4)
	{
		ft_putendl_fd(str, 2);
		// ft_putstr_fd(": command is not executable\n", 2);
		return (126);
	}
	return (1);
}