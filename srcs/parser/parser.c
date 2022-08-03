/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:35:41 by vmervin           #+#    #+#             */
/*   Updated: 2022/08/03 16:04:32 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	grammatic(t_parser *service)
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

static void	pathname_expansion(t_cmd *simpcmds, int *error)
{
	int	i;

	i = 0;
	if (!simpcmds)
		return ;
	while (!simpcmds[i].empty)
	{
		parse_word(simpcmds[i].infiles, INPUT);
		parse_word(simpcmds[i].outfiles, DEFAULT);
		parse_word(simpcmds[i].command, DEFAULT);
		parse_word(simpcmds[i].vars, VARIABLE);
		remove_empty(&simpcmds[i], error);
		i++;
	}
}

t_cmd	*parser(char *string, int *error)
{
	t_parser	service;
	t_cmd		*simplcmds;

	service.string = string;
	service.tokens = NULL;
	service.error = 0;
	simplcmds = NULL;
	grammatic(&service);
	if (!service.error)
		simplcmds = simple_command_parser(&service);
	if (!service.error)
		pathname_expansion(simplcmds, &service.error);
	if (!service.error)
		var_process(simplcmds);
	ft_lstclear(&service.tokens, free);
	*error = service.error;
	return (simplcmds);
}
