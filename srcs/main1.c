/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 03:49:26 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/14 05:37:59 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

t_global	g_var;

int	get_void_size(void **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

void	free_appropriate_struct(t_store *st)
{
	int	i;

	i = -1;
	if (st->com)
		while (++i < st->size)
			free(st->com[i]);
	i = -1;
	while (++i < st->size)
		free(st->par[i]);
	i = -1;
	while (++i < st->size - 1)
		free(st->pip[i]);
}

int	mini_err(t_store *st, int err)
{
	free_appropriate_struct(st);
	command_memfree(g_var.store->list);
	if (err == ERR_SUB_PRCCESS)
		exit(102);
	exit(1);
}

void	*mini_calloc(size_t nmemb, size_t size, t_store *st)
{
	char	*v;

	if (size && nmemb > (__SIZE_MAX__ / size))
		mini_err(st, ERR_CALLOC);
	v = malloc(nmemb * size);
	if (!v)
		mini_err(st, ERR_CALLOC);
	else
		return (ft_memset(v, '\0', (nmemb * size)));
	return (NULL);
}

int	get_cmd_size(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds[i].empty == 0)
		i++;
	return (i);
}
