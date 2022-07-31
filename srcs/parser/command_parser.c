/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:35:57 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/31 19:40:09 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	init_commands(t_cmd *cmd, t_parser *service, int i)
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

static int	search_pipes(t_list *lst)
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

t_cmd	*simple_command_parser(t_parser *service)
{
	int		count;
	t_cmd	*scmds;
	int		i;

	count = 0;
	count = search_pipes(service->tokens) + 1;
	scmds = malloc(sizeof(t_cmd) * (count + 1));
	if (!scmds)
		return (NULL);
	i = 0;
	while (i < count)
	{
		if (service->error)
			break ;
		init_commands(scmds + i, service, i);
		i++;
	}
	init_commands(scmds + i, NULL, i);
	return (scmds);
}
