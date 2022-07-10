/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:35:57 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/10 04:37:50 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	analize_syntax(t_cmd *cmd, t_list *lst, t_parser *service)
{
	int	x;

	x = 0;
	if (!service)
		return ;
	while (lst && ((t_token *)lst->content)->tokentype != '|'
		&& !service->error)
	{
		if (((t_token *)lst->content)->tokentype == '>')
			lst = add_iofile(&cmd->outfiles, lst->next, service, '>');
		else if (((t_token *)lst->content)->tokentype == '<')
			lst = add_iofile(&cmd->infiles, lst->next, service, '<');
		else if (!x && ((t_token *)lst->content)->tokentype == '=')
			lst = add_var_declare(cmd, lst, service, 0);
		else if (((t_token *)lst->content)->tokentype != ' ')
		{	
			if (x && ((t_token *)lst->content)->tokentype == '=')
				add_var_declare(cmd, lst, service, 1);
			lst = add_command(cmd, lst, service);
			x = 1;
		}
		else
			lst = lst->next;
	}
}

int	init_commands(t_cmd *cmd, t_parser *service, int i)
{
	t_list	*lst;

	if (!service)
		lst = NULL;
	else
		lst = service->tokens;
	cmd->outfiles = NULL;
	cmd->infiles = NULL;
	cmd->vars = NULL;
	cmd->command = NULL;
	cmd->empty = 0;
	if (!service)
		cmd->empty = 1;
	while (lst && (i > 0))
	{
		if (((t_token *)lst->content)->tokentype == '|')
			i--;
		lst = lst->next;
	}
	analize_syntax(cmd, lst, service);
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
