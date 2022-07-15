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

int	free_appropriate_struct(t_store *st, int err)
{
	int	i;
	int	e;

	free(st->com);
	i = -1;
	while (++i < st->size)
		free(st->par[i]);
	i = -1;
	while (++i < st->size - 1)
		free(st->pip[i]);
}

int	mini_err(t_store *st, int err)
{
	free_appropriate_struct(st, 0);
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
	v = malloc(nmemb * size); //malloc1
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

int	get_list_size(t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

char	*get_path_str(char **env)
{
	if (!env)
		return (NULL);
	while (ft_strncmp(*env, "PATH=", 5))
	{
		if (!*env)
			return (NULL);
		env++;
	}
	return (*env + 5);
}

int	startup(t_store *st, char **env)
{
	int	i;

	env_to_list(env);
	g_var.last_exec = 0;
	st->env = env;
	st->par = NULL;
	st->com = NULL;
	st->tempfile_dir = NULL;
	st->fd_in = dup(0);
	st->fd_out = dup(1);
	if (st->fd_in == -1 || st->fd_out == -1)
		mini_err(st, ERR_FORK_INIT);
	return (0);
}

void	malloc_appropriate_struct(t_store *st, t_cmd *cmds)
/* That func have inner protection. It's leaks free! */
{
	int	i;

	st->par = mini_calloc(st->size + 1, sizeof(void *), st);
	st->com = mini_calloc(st->size + 1, sizeof(void *), st);
	st->pip = mini_calloc(st->size, sizeof(void *), st);
	i = -1;
	while (++i < st->size)
	{
		st->pip[i] = mini_calloc(2, sizeof(int), st);
		st->par[i] = mini_calloc(get_list_size(cmds->command) + 1,
								sizeof(void *), st);
		cmds++;
	}
	i = -1;
	while (++i < st->size - 1)
	{
		if (pipe(st->pip[i]) == -1)
			mini_err(st, ERR_MALLOC0);
	}
	return ;
}

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
		st->com[i] = ((t_file *)curlist->content)->name;
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

int get_infile_fd_cycle(t_store *st, t_list *lst)
{
	int		temp_fd;

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

int	get_infile_fd2(t_store *st, t_cmd *cmds)
{
	// t_list	*lst;
	int		temp_fd;

	// lst = cmds->infiles;
	temp_fd = -1;
	// while (lst)
	// {
	// 	if (((t_file *)lst->content)->append == 0)
	// 	{
	// 		temp_fd = open(((t_file *)lst->content)->name,
	// 						O_RDONLY | O_CREAT, 0664);
	// 		if (temp_fd == -1)
	// 			mini_err(st, ERR_SUB_PRCCESS);
	// 		close(temp_fd);
	// 	}
	// 	else
	// 	{
	// 		temp_fd = open(st->tempfile_dir, O_RDWR | O_CREAT | O_TRUNC, 0664);
	// 		if (temp_fd == -1)
	// 			mini_err(st, ERR_SUB_PRCCESS);
	// 		heredoc(((t_file *)lst->content)->name, temp_fd,
	// 				((t_file *)lst->content)->append);
	// 		close(temp_fd);
	// 	}
	// 	lst = lst->next;
	// }
	temp_fd = get_infile_fd_cycle(st, cmds->infiles);
					// in progress //
	close(temp_fd);
	temp_fd = open(st->tempfile_dir, O_RDONLY, 0664);
	if (dup2(temp_fd, 0) == -1)
		mini_err(st, ERR_SUB_PRCCESS);
	if (temp_fd != -1)
		close(temp_fd);
	return (0);
}

int	get_infile_fd(t_store *st, t_cmd *cmds, int num)
{
	if (num > 0)
		close(st->pip[num - 1][1]);
	if (cmds->infiles == NULL)
	{
		if (num == 0)
			return (0);
		// printf("%d start listening\n", num);
		if (dup2(st->pip[num - 1][0], 0) == -1)
			mini_err(st, ERR_SUB_PRCCESS);
		// printf("%d stop listening\n", num);
		close(st->pip[num - 1][0]);
		return (0);
	}
	else
		get_infile_fd2(st, cmds);
	return (0);
}

int	get_outfile_fd2(t_store *st, t_cmd *cmds)
{
	t_list	*lst;
	int		temp_fd;

	lst = cmds->outfiles;
	temp_fd = -1;
	while (lst)
	{
		if (temp_fd != -1)
			close(temp_fd);
		if (((t_file *)lst->content)->append == 0)
			temp_fd = open(((t_file *)lst->content)->name,
						O_WRONLY | O_TRUNC | O_CREAT, 0664);
		else
			temp_fd = open(((t_file *)lst->content)->name,
						O_WRONLY | O_APPEND | O_CREAT, 0664);
		if (temp_fd == -1)
			mini_err(st, ERR_SUB_PRCCESS);
		lst = lst->next;
	}
	if (dup2(temp_fd, 1) == -1)
		mini_err(st, ERR_SUB_PRCCESS);
	if (temp_fd != -1)
		close(temp_fd);
	return (0);
}

// int	 get_infile_fd(t_store *st, t_cmd *cmds, int num)
// {
// 	if (num < st->size - 1)
// 		close(st->pip[num][0]);
// 	if (cmds->outfiles == NULL)
// 	{
// 		if (num == st->size - 1)
// 		{
// 			// printf("its a finish, Mariio!\n");
// 			return (0);
// 		}
// 		if (dup2(st->pip[num][1], 1) == -1)
// 		{
// 			mini_err(st, ERR_SUB_PRCCESS);
// 		}
// 		close(st->pip[num - 1][0]);
// 		return (0);
// 	}
// 	else
// 		get_outfile_fd2(st, cmds);
// 	return (0);
// }

int	get_outfile_fd(t_store *st, t_cmd *cmds, int num)
{
	if (num < st->size - 1)
		close(st->pip[num][0]);
	if (cmds->outfiles == NULL)
	{
		if (num == st->size - 1)
			return (0);
		if (dup2(st->pip[num][1], 1) == -1)
		{
			mini_err(st, ERR_SUB_PRCCESS);
		}
		close(st->pip[num][1]);
		return (0);
	}
	get_outfile_fd2(st, cmds);
	return (0);
}

int	find_file_by_dir(t_store *st, char **com, int e)
{
	int		i;
	char	*str;

	i = -1;
	while (++i < st->path_size)
	{
		str = strjoin_char(st->path[i], st->com[e], '/');
		if (!str)
			mini_err(st, 0);
		if (access(str, F_OK) == 0)
		{
			com[e] = str;
			return (1);
		}
		free(str);
	}
	return (0);
}

int	is_command_ok(t_store *st)
{
	int	i;

	i = -1;
	while (++i < st->size)
	{
		if (built_in_check(st->par[i][0]))
			continue ;
		if (find_file_by_dir(st, st->com, i) == 0)
		{
			printf("minishell: %s: command not found\n", st->par[i][0]);
			return (0);
		}
		// printf("%d) %s\n", i, st->com[i]);
	}
	return (1);
}

int	close_exceed_fd(t_store *st, int num)
{
	if (num > 0)
	{
		close(st->pip[num - 1][0]);
		close(st->pip[num - 1][1]);
	}
	if (num < st->size - 1)
	{
		close(st->pip[num][0]);
		close(st->pip[num][1]);
	}
}

int	pipe_exec_subfunc(t_store *st, t_cmd *cmds, int num)
{
	int	status;

	get_infile_fd(st, cmds, num);
	get_outfile_fd(st, cmds, num);
	// close(st->pip[num][0]);
	// close(st->pip[num][1]);
	// close(st->pip[num - 1][0]);
	// close(st->pip[num - 1][1]);
	// close_exceed_fd(st, num);
	if (!is_built_in(cmds->command)) // built-in in progress
		exit(0);
	// printf("%s st->com[num]\n", st->com[num]);
	st->last_result = execve(st->com[num], st->par[num], st->env);
	if (st->last_result == -1)
		mini_err(st, ERR_FOR_SUBFUNC);
	exit(0);
	return (0);
}

void	test_func(t_store *st, t_cmd *cmds, int num)
{
	printf("%d fork start\n", num);
	// printf("%d) command: %s\n", num, st->par[num][0]);
	// int i = 1;
	// while (st->par[num][i])
	// {
	// 	printf("%d) arg[%d]: %s\n", num, i, st->par[num][i]);
	// 	i++;
	// }
}

int	pipe_exec(t_store *st, t_cmd *cmds, int num)
{
	int	pid;
	int	status;

	// test_func(st, cmds, num);
	pid = fork();
	if (pid < 0)
		mini_err(st, ERR_FORK_INIT);
	if (pid == 0)
	{
		pipe_exec_subfunc(st, cmds, num);
	}
	else
	{
		// // printf("%d philo thinking\n", num);
		// // close(st->pip[num][0]);
		// printf("fd: %d\n", st->pip[num][1]);
		if (num < st->size - 1)
			close(st->pip[num][1]);
		waitpid(pid, &status, 0);
		// printf("%d wifexited = %d\n", num, WIFEXITED(status));
		if (!WIFEXITED(status))
			mini_err(st, 102);
		if (WEXITSTATUS(status) == 103)
			mini_err(st, 102);
		// printf("%d philo eating\n", num);
	}
	return (pid);
}

int	main_loop(t_store *st, t_cmd *cmds)
{
	int	i;
	int	e;
	int	pid;
	int	status;

	malloc_appropriate_struct(st, cmds);
	create_appropriate_struct(st, cmds);
	if (!st->tempfile_dir)
		st->tempfile_dir = strjoin_char(get_var("HOME"),
							".minishell_tempfile", '/');
	i = -1;
	if (!is_command_ok(st))
		return (0);
	while (++i < st->size)
	{
		pid = pipe_exec(st, cmds + i, i);
		if (pid == -1)
			break ;
	}
	i = -1;
	// dup2(0, st->fd_in);
	// dup2(1, st->fd_out);
	// while (++i < st->size - 1)
	// {
	// 	e = -1;
	// 	while (++e < 0)
	// 		close(st->pip[i][e]);
	// }
	// waitpid(pid, &status, 0);
	// unlink(st->tempfile_dir);
	g_var.last_exec = WEXITSTATUS(status);
	return (0);
}

int	main(int args, char **argv, char **env)
{
	t_store	st;
	int		err;
	t_cmd	*cmds;
	char	*str;

	if (startup(&st, env))
		return (0);
	g_var.store = &st;
	while (1)
	{
		// printf("	imhere\n");
		str = rl_gets();
		if (!str || !*str)
			continue;
		cmds = parser(str, &err);
		st.list = cmds;
		if (err)
			continue;
		st.env = list_to_env();
		// test_print_env(st.env;)
		st.path = ft_split(get_var("PATH"), ':');
		if (!st.path || !st.env)
			mini_err(&st, 0);
		st.path_size = get_void_size((void *)st.path);
		st.size = get_cmd_size(cmds);
		err = main_loop(&st, cmds);
	}
}
