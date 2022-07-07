/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:35:41 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/07 13:38:07 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*parser(char *string)
{
	t_list	*tokens;
	t_cmd	*simplcmds;

	tokens = NULL;
	g_var.error = 0;
	if (string == "\n")
		return (NULL);
	grammatic(&tokens, string);
	simplcmds = simple_command_parser(tokens, string);
	pathname_expansion(simplcmds);
	ft_lstclear(&tokens, free);
	return (simplcmds);
}

void	grammatic(t_list **tokens, char *string)
{
	quote_token_search(tokens, '\"', string);
	one_simbol_token_search(tokens, '|', string);
	one_simbol_token_search(tokens, '>', string);
	one_simbol_token_search(tokens, '<', string);
	space_token_search(tokens, "\t\n ", string);
	word_token_search(tokens, string);
	equal_token_search(tokens, string);
	word_token_search(tokens, string);
	ft_list_sort(tokens, compare_tokens);
}

t_cmd	*simple_command_parser(t_list *lst, char *str)
{
	int		count;
	t_cmd	*scmds;
	int		i;

	count = 0;
	count = search_pipes(lst) + 1;
	scmds = malloc(sizeof(t_cmd) * (count + 1));
	if (!scmds)
		return (NULL);
	i = 0;
	while (i < count && !g_var.error)
	{
		init_commands(&scmds[i], lst, str, i);
		i++;
	}
	init_commands(&scmds[i], NULL, NULL, i);
	return (scmds);
}

void	pathname_expansion(t_cmd *simpcmds)
{
	int	i;

	i = 0;
	if (!simpcmds)
		return ;
	while (!simpcmds[i].empty)
	{
		parse_word(simpcmds[i].infiles, 0);
		parse_word(simpcmds[i].outfiles, 0);
		parse_word(simpcmds[i].command, 0);
		parse_word(simpcmds[i].vars, 1);
		i++;
	}
}
