/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:35:41 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/12 07:58:15 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*parser(char *string, int *error)
{
	t_parser	service;
	t_cmd		*simplcmds;

	service.string = string;
	service.tokens = NULL;
	service.error = 0;
	simplcmds = NULL;
	// if (!ft_strncmp(string, "\n", ft_strlen(string)))
	// 	return (NULL);
	grammatic(&service);
	if (!service.error)
		simplcmds = simple_command_parser(&service);
	if (!service.error)
		pathname_expansion(simplcmds, &service.error);
	if (!service.error)
		var_process(simplcmds);
	ft_lstclear(&service.tokens, free);
	*error = service.error;
	// lstprint2(cmds[0].command);
	// lstprint2(cmds[0].vars);
	return (simplcmds);
}

void	grammatic(t_parser *service)
{
	quote_token_search(service);
	one_simbol_token_search(&service->tokens, '|', service->string);
	one_simbol_token_search(&service->tokens, '>', service->string);
	one_simbol_token_search(&service->tokens, '<', service->string);
	space_token_search(&service->tokens, "\t ", service->string);
	word_token_search(&service->tokens, service->string);
	equal_token_search(&service->tokens, service->string);
	word_token_search(&service->tokens, service->string);
	ft_list_sort(&service->tokens, compare_tokens);
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
		init_commands(&scmds[i], service, i);
		i++;
	}
	init_commands(&scmds[i], NULL, i);
	return (scmds);
}

void	pathname_expansion(t_cmd *simpcmds, int *error)
{
	int	i;

	i = 0;
	if (!simpcmds)
		return ;
	while (!simpcmds[i].empty)
	{
		parse_word(simpcmds[i].infiles, -1);
		parse_word(simpcmds[i].outfiles, 0);
		parse_word(simpcmds[i].command, 0);
		parse_word(simpcmds[i].vars, 1);
		remove_empty(&simpcmds[i], error);
		i++;
	}
}