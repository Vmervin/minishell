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

void	create_appropriate_struct(t_store *st, t_cmd *cmds)
{
	int		i;
	int		e;
	t_list	*curlist;

	i = -1;
	while (++i < st->size)
	{
		if (!cmds->command)
			continue ;
		e = 0;
		curlist = (cmds + i)->command;
		while (curlist)
		{
			st->par[i][e] = ((t_file *)curlist->content)->name;
			curlist = curlist->next;
			e++;
		}
		st->par[i][e] = NULL;
	}
}

size_t	strlen_protected(const char *s)
{
	unsigned long	size;

	if (!s)
		return (0);
	size = 0;
	while (*s != '\0')
	{
		s++;
		size++;
	}
	return (size);
}

int	strcat_add(char **s1, char *s2)
{
	char	*out;
	int		size1;
	int		size2;
	int		i;

	if (!(*s1) && !s2)
		return (0);
	size1 = strlen_protected((*s1));
	size2 = strlen_protected(s2);
	out = malloc((size1 + size2 + 1) * sizeof(char));
	if (!out)
		mini_err(g_var.store, ERR_MALLOC0);
	if (!out)
		return (1);
	i = -1;
	while (++i < size1)
		out[i] = (*s1)[i];
	size1 = -1;
	while (++size1 <= size2)
		out[i++] = s2[size1];
	free((*s1));
	(*s1) = out;
	return (0);
}

char	*strjoin_char(char *s1, char *s2, char delim)
{
	char	*out;
	int		size1;
	int		size2;
	int		i;

	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	out = malloc((size1 + size2 + 2) * sizeof(char));
	if (!out)
		return (NULL);
	i = -1;
	while (++i < size1)
		out[i] = s1[i];
	out[i++] = delim;
	size1 = -1;
	while (++size1 <= size2)
		out[i++] = s2[size1];
	return (out);
}

int	get_infile_fd_cycle(t_store *st, t_list *lst)
{
	int	temp_fd;

	temp_fd = -1;
	while (lst)
	{
		if (((t_file *)lst->content)->append == 0)
		{
			temp_fd = open(((t_file *)lst->content)->name,
					O_RDONLY | O_CREAT, 0664);
			if (temp_fd == -1)
				mini_err(st, ERR_SUB_PRCCESS);
			close(temp_fd);
		}
		else
		{
			temp_fd = open(st->tempfile_dir, O_RDWR | O_CREAT | O_TRUNC, 0664);
			if (temp_fd == -1)
				mini_err(st, ERR_SUB_PRCCESS);
			heredoc(((t_file *)lst->content)->name, temp_fd,
				((t_file *)lst->content)->append);
			close(temp_fd);
		}
		lst = lst->next;
	}
	return (temp_fd);
}
