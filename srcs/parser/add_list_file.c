/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_list_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:36:03 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/07 13:53:26 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_list_file(t_list **lst, int append, char *name, char *value)
{
	t_file	*content;

	content = malloc(sizeof(t_file));
	content->append = append;
	content->name = name;
	content->value = value;
	ft_lstadd_back(lst, ft_lstnew(content));
}

t_list	*add_outfile(t_cmd *cmd, t_list *lst, char *str)
{
	int	begin;
	int	end;
	int	append;

	append = 0;
	if (((t_token *)lst->content)->tokentype == '>')
	{
		append = 1;
		lst = lst->next;
	}
	while (lst && ((t_token *)lst->content)->tokentype == ' ')
		lst = lst->next;
	if (ft_strchr(">|<", ((t_token *)lst->content)->tokentype))
	{	
		syntax_error(((t_token *)lst->content)->tokentype);
		return (NULL);
	}
	begin = ((t_token *)lst->content)->begin;
	end = ((t_token *)lst->content)->end;
	while (lst && ft_strchr("w$\'\"=", ((t_token *)lst->content)->tokentype))
	{
		if (end < ((t_token *)lst->content)->end)
			end = ((t_token *)lst->content)->end;
		lst = lst->next;
	}
	add_list_file(&cmd->outfiles, append,
		ft_substr(str, begin, end - begin + 1), NULL);
	return (lst);
}

t_list	*add_infile(t_cmd *cmd, t_list *lst, char *str)
{
	int	begin;
	int	end;

	if (((t_token *)lst->content)->tokentype == '<')
	{
		// here_doc это совсем другая история
		lst = lst->next;
	}
	while (lst && ((t_token *)lst->content)->tokentype == ' ')
		lst = lst->next;
	if (ft_strchr(">|<", ((t_token *)lst->content)->tokentype))
	{	
		syntax_error(((t_token *)lst->content)->tokentype);
		return (NULL);
	}
	begin = ((t_token *)lst->content)->begin;
	end = ((t_token *)lst->content)->end;
	while (lst && ft_strchr("w$\'\"=", ((t_token *)lst->content)->tokentype))
	{
		if (end < ((t_token *)lst->content)->end)
			end = ((t_token *)lst->content)->end;
		lst = lst->next;
	}
	add_list_file(&cmd->infiles, 0,
		ft_substr(str, begin, end - begin + 1), NULL);
	return (lst);
}

t_list	*add_var_declare(t_cmd *cmd, t_list *lst, char *str)
{
	int		begin;
	int		end;
	char	*name;

	begin = ((t_token *)lst->content)->begin;
	end = ((t_token *)lst->content)->end;
	name = ft_substr(str, begin, end - begin);
	begin = end + 1;
	lst = lst->next;
	while (lst && ft_strchr("w$\'\"=", ((t_token *)lst->content)->tokentype))
	{
		if (end < ((t_token *)lst->content)->end)
			end = ((t_token *)lst->content)->end;
		lst = lst->next;
	}
	add_list_file(&cmd->vars, 0, name,
		ft_substr(str, begin, end - begin + 1));
	return (lst);
}

t_list	*add_command(t_cmd *cmd, t_list *lst, char *str)
{
	int	begin;
	int	end;

	begin = ((t_token *)lst->content)->begin;
	end = ((t_token *)lst->content)->end;
	while (lst && ft_strchr("w$\'\"=", ((t_token *)lst->content)->tokentype))
	{
		if (end < ((t_token *)lst->content)->end)
			end = ((t_token *)lst->content)->end;
		lst = lst->next;
	}
	add_list_file(&cmd->command, 0,
		ft_substr(str, begin, end - begin + 1), NULL);
	cmd->delim = 1;
	return (lst);
}
