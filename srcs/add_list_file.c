/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_list_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:36:03 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/09 03:28:53 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	add_list_file(t_list **lst, int append, char *name, char *value)
{
	t_file	*content;

	content = malloc(sizeof(t_file));
	if (!content)
	{
		if (name)
			free (name);
		if (value)
			free (value);
		return (1000);
	}
	content->append = append;
	content->name = name;
	content->value = value;
	ft_lstadd_back(lst, ft_lstnew(content));
	return (0);
}

t_list	*skip_space(t_list *lst, t_parser *service, int *append, int type)
{
	if (((t_token *)lst->content)->tokentype == type)
	{
		*append = 1;
		lst = lst->next;
	}
	while (lst && ((t_token *)lst->content)->tokentype == ' ')
		lst = lst->next;
	if (ft_strchr(">|<", ((t_token *)lst->content)->tokentype))
		service->error = syntax_error(((t_token *)lst->content)->tokentype);
	return (lst);
}

t_list	*add_iofile(t_list **cmd, t_list *lst, t_parser *service, char type)
{
	int	begin;
	int	end;
	int	append;
	int	tmp;

	append = 0;
	tmp = 0;
	lst = skip_space(lst, service, &append, type);
	if (service->error)
		return (NULL);
	begin = ((t_token *)lst->content)->begin;
	end = ((t_token *)lst->content)->end;
	while (lst && ft_strchr("w$\'\"=", ((t_token *)lst->content)->tokentype))
	{
		if (end < ((t_token *)lst->content)->end)
			end = ((t_token *)lst->content)->end;
		lst = lst->next;
	}
	tmp = 0;
	tmp = add_list_file(cmd, append,
			ft_substr(service->string, begin, end - begin + 1), NULL);
	if (tmp)
		service->error = tmp;
	return (lst);
}

t_list	*add_var_declare(t_cmd *cmd, t_list *lst, t_parser *service)
{
	int		begin;
	int		end;
	char	*name;
	int		tmp;

	begin = ((t_token *)lst->content)->begin;
	end = ((t_token *)lst->content)->end;
	name = ft_substr(service->string, begin, end - begin);
	begin = end + 1;
	lst = lst->next;
	while (lst && ft_strchr("w$\'\"=", ((t_token *)lst->content)->tokentype))
	{
		if (end < ((t_token *)lst->content)->end)
			end = ((t_token *)lst->content)->end;
		lst = lst->next;
	}
	tmp = 0;
	tmp = add_list_file(&cmd->vars, 0, name,
			ft_substr(service->string, begin, end - begin + 1));
	if (tmp)
		service->error = tmp;
	return (lst);
}

t_list	*add_command(t_cmd *cmd, t_list *lst, t_parser *service)
{
	int	begin;
	int	end;
	int	tmp;

	begin = ((t_token *)lst->content)->begin;
	end = ((t_token *)lst->content)->end;
	while (lst && ft_strchr("w$\'\"=", ((t_token *)lst->content)->tokentype))
	{
		if (end < ((t_token *)lst->content)->end)
			end = ((t_token *)lst->content)->end;
		lst = lst->next;
	}
	tmp = 0;
	tmp = add_list_file(&cmd->command, 0,
			ft_substr(service->string, begin, end - begin + 1), NULL);
	if (tmp)
		service->error = tmp;
	return (lst);
}
