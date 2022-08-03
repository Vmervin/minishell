/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analize_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 23:17:28 by vmervin           #+#    #+#             */
/*   Updated: 2022/08/03 16:46:02 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*skip_space(t_list *lst, t_parser *service, int *append, int type)
{
	if (!lst)
	{
		service->error = syntax_error(NEW_LINE);
		return (lst);
	}
	if (((t_token *)lst->content)->tokentype == type)
	{
		*append = 1;
		lst = lst->next;
	}
	if (!lst)
	{
		service->error = syntax_error(NEW_LINE);
		return (lst);
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

t_list	*add_var_declare(t_cmd *cmd, t_list *lst, t_parser *service, int exprt)
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
	tmp = add_list_file(&cmd->vars, exprt, name,
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
