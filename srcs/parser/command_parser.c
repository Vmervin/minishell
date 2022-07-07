/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:35:57 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/07 13:40:49 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	analize_syntax(t_cmd *cmd, t_list *lst, char *str)
{
	int	x;

	x = 0;
	while (lst && ((t_token *)lst->content)->tokentype != '|')
	{
		if (((t_token *)lst->content)->tokentype == '>')
			lst = add_outfile(cmd, lst->next, str);
		else if (((t_token *)lst->content)->tokentype == '<')
			lst = add_infile(cmd, lst->next, str);
		else if (!x && ((t_token *)lst->content)->tokentype == '=')
			lst = add_var_declare(cmd, lst, str);
		else if (((t_token *)lst->content)->tokentype != ' ')
		{	
			lst = add_command(cmd, lst, str);
			x = 1;
		}
		else
			lst = lst->next;
	}
}

int	init_commands(t_cmd *cmd, t_list *lst, char *str, int i)
{
	cmd->outfiles = NULL;
	cmd->infiles = NULL;
	cmd->vars = NULL;
	cmd->command = NULL;
	cmd->delim = 0;
	cmd->empty = 0;
	if (!lst && !str)
		cmd->empty = 1;
	while (lst && (i > 0))
	{
		if (((t_token *)lst->content)->tokentype == '|')
			i--;
		lst = lst->next;
	}
	analize_syntax(cmd, lst, str);
	return (0);
}

int	search_pipes(t_list *lst)
{
	int	count;

	count = 0;
	while (lst && lst->next)
	{
		if (((t_token *)lst->content)->tokentype == '|')
			count++;
		lst = lst->next;
	}
	return (count);
}
