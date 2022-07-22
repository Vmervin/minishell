/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 19:42:33 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/22 22:12:13 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_global g_var;

// int	mini_err(t_store *st, int err)
// {
// 	printf("errno: %d\n", errno);
// 	printf("Err occured: %d\n", err);
// 	if (err == 0)
// 	{
// 		free(st->par);
// 	}
// 	exit(1);
// }

// int	error_mess(char *name, int mode, char *str)
// {
// 	ft_putstr_fd("minishell: ", 2);
// 	ft_putstr_fd(name, 2);
// 	ft_putchar_fd(' ', 2);
// 	if (mode == 1)
// 		ft_putendl_fd(str, 2);
// 		// ft_putstr_fd(": No such file or directory\n", 2);
// 	if (mode == 2)
// 		ft_putendl_fd(str, 2);
// 		// ft_putstr_fd(": Access denied\n", 2);
// 	if (mode == 3)
// 	{
// 		ft_putstr_fd(": command not found\n", 2);
// 		return (127);
// 	}
// 	if (mode == 4)
// 	{
// 		ft_putendl_fd(str, 2);
// 		// ft_putstr_fd(": command is not executable\n", 2);
// 		return (126);
// 	}
// 	return (1);
// }

// int heredoc_proc(t_list *lst, t_info *info)
// {
// 	int herdoc;

// 	info->fdin = dup(0);
// 	dup2(info->tmpin, 0);
// 	info->hd = ft_strjoin_free(get_var("HOME"), ft_strdup("/"));
// 	info->hd = ft_strjoin_free(info->hd, ft_strdup(".HERE_DOCUMENT"));
// 	herdoc = open(info->hd, O_WRONLY | O_CREAT | O_TRUNC, 0664);// need to close and then reopen
// 	heredoc(((t_file *)(lst->content))->name, herdoc, ((t_file *)(lst->content))->append);
// 	dup2(info->fdin, 0);
// 	close(info->fdin);
// 	close(herdoc);
// 	info->fdin = open(info->hd, O_RDONLY, 0664);
// 	return (0);
// }

// int	open_in(t_cmd cmd, t_info *info)
// {
// 	t_list *lst;

// 	lst = cmd.infiles;
// 	if (!lst)
// 		return (1);
// 	info->fdin = -1;
// 	while (lst)
// 	{
// 		if (((t_file *)(lst->content))->append)
// 		{
// 			heredoc_proc(lst, info);
// 		}
// 		else
// 			info->fdin = open(((t_file *)(lst->content))->name, O_RDONLY);
// 		if (info->fdin < 0)
// 		{
// 			info->res = error_mess(((t_file *)(lst->content))->name, 1, strerror(errno));
// 			return (1);
// 		}
// 		lst = lst->next;		
// 	}
// 	return (0);
// }

// int	open_out(t_cmd cmd, t_info *info)
// {
// 	t_list *lst;

// 	lst = cmd.outfiles;
// 	if (!lst)
// 		return (1);
// 	info->fdout = -1;
// 	while (lst)
// 	{
// 		if (((t_file *)(lst->content))->append)
// 		{
// 			info->fdout = open(((t_file *)(lst->content))->name,
// 						O_WRONLY | O_CREAT | O_APPEND, 0664);
// 		}
// 		else
// 		{
// 			info->fdout = open(((t_file *)(lst->content))->name,
// 						O_WRONLY | O_CREAT | O_TRUNC, 0664);
// 		}
// 		if (info->fdout < 0)
// 		{
// 			info->res = error_mess(((t_file *)(lst->content))->name, 2, strerror(errno));
// 			return (1);
// 		}
// 		lst = lst->next;		
// 	}
// 	return (0);
// }

// int	open_loop(t_cmd cmd, t_info *info)
// {
// 	if (!open_in(cmd, info))
// 	{
// 		dup2(info->fdin, 0);
// 		close(info->fdin);
// 	}
// 	if (!open_out(cmd, info))
// 	{
// 		dup2(info->fdout, 1);
// 		close(info->fdout);
// 	}
// 	return (0);
// }

int cmdlen(t_cmd *cmds)
{
	int i;

	i = 0;
	while (!cmds[i].empty)
		i++;
	return (i);
}

// // close all fd in child
// int fd_closer(int num, int (*fdpipe)[2])
// {
// 	int i;

// 	i = 0;
// 	while (i < num)
// 	{
// 		close(fdpipe[i][0]);
// 		close(fdpipe[i][1]);
// 		i++;
// 	}
// 	return (0);
// }

// char	**list_to_argv(t_list *lst)
// {
// 	t_list	*tmp;
// 	int		i;
// 	char	**env;

// 	i = ft_lstsize(lst) + 1;
// 	tmp = lst;
// 	env = malloc(sizeof(char **) * i);
// 	i = 0;
// 	while (env && tmp)
// 	{
// 		env[i] = ft_strdup(((t_file *)(tmp->content))->name);
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	env[i] = NULL;
// 	return (env);
// }

// int free_path(char **path)
// {
// 	int i;

// 	i = 0;
// 	while(path[i])
// 	{
// 		free(path[i]);
// 		i++;
// 	}
// 	free(path);
// 	return (0);
// }

// char *get_path(char *args, char *path, int *error)
// {
// 	char	*res;
// 	int		i;
// 	int		acc;
// 	char	**true_path;

// 	i = 0;
// 	true_path = ft_split(path, ':');
// 	while (true_path[i])
// 	{
// 		res = ft_strjoin(true_path[i], "/");
// 		res = ft_strjoin_free(res, ft_strdup(args));
// 		acc = access(res, F_OK);
// 		if (!acc)
// 		{
// 			free(args);
// 			free_path(true_path);
// 			return (res);
// 		}
// 		free(res);
// 		i++;
// 	}
// 	if (acc < 0)
// 		perror("access");// this message for debug only, remove it from final version
// 	*error = error_mess(args, 3, strerror(errno));
// 	free_path(true_path);
// 	free(args);
// 	return (NULL);
// }

// int exe_command(t_info *info)
// {
// 	// char **args;
// 	int	error;

// 	fd_closer(info->len - 1, info->fdpipe);
// 	// if (!cmd.command)
// 	// 	exit(0);
// 	// if (built_in_check(((t_file *)cmd.command->content)->name))
// 	// 	exit(0);
// 	error = 0;
// 	// args = list_to_argv(cmd.command);
// 	// if (!ft_strchr(args[0], '/') && info->path)
// 	// 	args[0] = get_path(args[0], info->path, &error);
// 	if (info->args[0])
// 	{
// 		if (access(info->args[0], X_OK))
// 			error = error_mess(info->args[0], 4, strerror(errno));
// 		ft_putstr_fd("kek\n", 2);
// 		execve(info->args[0], info->args, info->env);
// 		perror("execve");// this message for debug only, remove it from final version
// 	}
// 	exit(error);
// }

// int waitress(t_info *info,  int i)
// {
// 	int error;

// 	if (info->pid[i] < 0)
// 		return (0);
// 	waitpid(info->pid[i], &error, 0);// $?
// 	if (WIFEXITED(error))
// 		info->res = WEXITSTATUS(error);
// 	if (WIFSIGNALED(error))
// 		info->res = WTERMSIG(error) + 128;
// 	return (0);
// }

// int	in_outpipe(t_info *info, int i, int in)
// {
// 	if (in)
// 	{
// 		if (i < info->len - 1)
// 		{
// 			dup2(info->fdpipe[i][1], 1);
// 			close(info->fdpipe[i][1]);
// 		}
// 		else
// 			dup2(info->tmpout, 1);
// 	}
// 	else
// 	{
// 		if (i < info->len - 1)
// 		{
// 			dup2(info->fdpipe[i][0], 0);
// 			close(info->fdpipe[i][0]);
// 		}
// 	}
// 	return (0);
// }

// int child_birth(t_cmd *cmds, t_info *info, int i)
// {
// 	int error;

// 	error = 0;
// 	info->args = list_to_argv(cmds[i].command);
// 	if (!ft_strchr(info->args[0], '/') && info->path)
// 		info->args[0] = get_path(info->args[0], info->path, &error);
// 	if (!error)
// 		info->pid[i] = fork();
// 	if (!info->pid[i])
// 	{
// 		exe_command(info);
// 	}
// 	free_path(info->args);
// 	return(error);
// }

// int command_executor(t_cmd *cmds, t_info *info, int i)
// {
// 	info->res = 0;
// 	in_outpipe(info, i, 1);
// 	open_loop(cmds[i], info);
// 	if (info->res)
// 		return (1);
// 	if (cmds[i].command)
// 	{
// 		if (built_in_check(((t_file *)cmds[i].command->content)->name))
// 			info->res = is_built_in(cmds[i].command, !i, info);
// 		else
// 			info->res = child_birth(cmds, info, i);
// 	}
// 	waitress(info, i);
// 	in_outpipe(info, i, 0);
// 	if (info->hd)
// 		unlink(info->hd);
// 	return (0);
// }

// int pipe_memfree(t_info info)
// {
// 	int i;

// 	i = 0;
// 	while(info.env[i])
// 	{
// 		free(info.env[i]);
// 		i++;
// 	}
// 	free(info.env);
// 	free(info.path);
// 	free(info.pid);
// 	free(info.fdpipe);
// 	return (0);
// }

/*int piper(int (**fdpipe)[2], int len)
{
	int i;

	fdpipe = malloc((len - 1) * sizeof(*fdpipe));
	i = 0;
	while (i < len - 1)
	{
		if (pipe(*fdpipe[i++]) < 0)// close if failed
			perror("pipe");
	}
	return (0);
}*/

// // close pipes if failed
// int	pipe_error(t_info *info, int i)
// {
// 	int j;

// 	j = 0;
// 	perror("pipe");
// 	while (j < i)
// 	{
// 		close(info->fdpipe[j][0]);
// 		close(info->fdpipe[j][1]);
// 		j++;
// 	}	
// 	pipe_memfree(*info);
// 	return (1);
// }

// int init_pid(t_info *info, int len)
// {
// 	int i;

// 	info->pid = malloc(len * sizeof(int));
// 	i = 0;
// 	while (i < len)
// 		info->pid[i++] = -1;
// 	return (0);
// }

// int init_pipe(t_info *info, int len, t_cmd *cmds)
// {
// 	int i;

// 	info->res = 0;
// 	info->len = len;
// 	info->cmds = cmds;
// 	info->args = NULL;
// 	info->hd = NULL;
// 	info->tmpin = dup(0);
// 	info->tmpout = dup(1);
// 	info->fdpipe = malloc((len - 1) * sizeof(*info->fdpipe));
// 	i = 0;
// 	while (i < len - 1)
// 	{
// 		if (pipe(info->fdpipe[i++]) < 0)
// 			return (pipe_error(info, i));
// 	}
// 	info->env = list_to_env();
// 	info->path = get_var("PATH");
// 	init_pid(info, len);
// 	return (0);
// }

int main_loop(t_cmd *cmds, int len)
{
	int i;
	t_info info;

	i = 0;
	if (init_pipe(&info, len, cmds))
		return (1);
	while (i < len)
	{
		command_executor(cmds, &info, i);
		i++;
	}
	dup2(info.tmpin, 0);
	dup2(info.tmpout, 1);
	ft_putstr_fd("lol\n", 2);
	close(info.tmpin);
	close(info.tmpout);
	pipe_memfree(info);
	printf("res=%d\n", info.res);
	return (info.res);
}

// still reachable: 113,611 bytes in 181 blocks
// still reachable: 113,751 bytes in 190 blocks
// still reachable: 119,096 bytes in 199 blocks
int	main(int argc, char **argv, char **env)
{
	int		err;
	t_cmd	*cmds;
	char	*str;
	(void)argc;
	(void)argv;

	env_to_list(env);
	while (1)
	{
		str = rl_gets();
		if (!str || !*str)
			continue ;
		cmds = parser(str, &err);
		if (err)
		{
			g_var.last_exec = err;
			command_memfree(cmds);
			free(str);
			continue ;
		}
		g_var.last_exec = main_loop(cmds, cmdlen(cmds));
		command_memfree(cmds);
		free(str);
	}
}
