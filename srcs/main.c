#include "../includes/minishell.h"

// void	free_appropriate_struct(t_store *st)
// {
	
// }

t_global g_var;

int	mini_err(t_store *st, int err)
{
	printf("errno: %d\n", errno);
	printf("Err occured: %d\n", err);
	if (err == 0)
	{
		free(st->com);
		free(st->par);
	}
	exit(1);
}

void	*mini_calloc(size_t nmemb, size_t size, t_store *st)
{
	char	*v;

	if (size && nmemb > (__SIZE_MAX__ / size))
		mini_err(st, ERR_MALLOC0);
	v = malloc(nmemb * size);
	if (!v)
		mini_err(st, ERR_MALLOC0);
	else
		return (ft_memset(v, '\0', (nmemb * size)));
	return (NULL);
}

int	get_cmd_size(t_cmd *cmds)
{
	int i;

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

char	**path_separate(char **env)
{
	char	*path_str;
	char	**pathes;

	path_str = get_path_str(env);
	if (!path_str)
		return (NULL);
	pathes = ft_split(path_str, ':');
	return (pathes);
}

int	startup(t_store *st, char **env)
{
	int	i;

	st->in = dup(0);
	st->out = dup(1);
	if (st->in == -1 || st->out == -1)
		mini_err(st, ERR_MALLOC0);
	env_to_list(env);
	st->path = path_separate(env);
	st->env = env;
	if (!st->path)
		return (1);
	return (0);
	st->com = NULL;
	st->par = NULL;
}

void	malloc_appropriate_struct(t_store *st, t_cmd *cmds)
/* That func have inner protection. It's leaks free! */
{
	int	i;

	st->com = mini_calloc(st->size + 1, sizeof(void *), st);
	st->par = mini_calloc(st->size + 1, sizeof(void *), st);
	st->pip = mini_calloc(st->size, sizeof(void *), st);
	i = -1;
	while (++i < st->size)
	{
		st->pip[i] = mini_calloc(2, sizeof(int), st);
		st->par[i] = mini_calloc(get_list_size(cmds->command) + 1, sizeof(void *), st);
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
		st->com[i] = ((t_file *)(cmds + i)->command->content)->name;
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

int	 get_infile_fd(t_store *st, t_cmd *cmds, int num)
{
	t_list	*lst;
	int		temp_fd;
	int		fd_out;

	if (cmds->infiles == NULL)
	{
		if (num == 0)
			return (0);
		close(st->pip[num - 1][1]);
		if (dup2(st->pip[num - 1][0], 0) == -1)
			mini_err(st, ERR_SUB_PRCCESS);
		return (0);
	}
	lst = cmds->infiles;
	while (lst->next)
	{
		temp_fd = open(((t_file *)lst->content)->name, O_WRONLY | O_TRUNC | O_CREAT, 0664);
		if (temp_fd == -1)
			mini_err(st, ERR_SUB_PRCCESS);
		lst = lst->next;
	}
	if (((t_file *)lst->content)->append == 1)
		temp_fd = open(((t_file *)lst->content)->name, O_RDONLY);
	if (temp_fd == -1)
		mini_err(st, ERR_SUB_PRCCESS);
	if (dup2(temp_fd, 0) == -1)
		mini_err(st, ERR_SUB_PRCCESS);
	return (0);
}

int	get_outfile_fd(t_store *st, t_cmd *cmds, int num)
{
	t_list	*lst;
	int		temp_fd;

	if (cmds->outfiles == NULL)
	{
		if (num == st->size - 1)
			return (0);

		if (dup2(st->pip[num][1], 1) == -1)
		{
			close(st->pip[num][1]);
			mini_err(st, ERR_SUB_PRCCESS);
		}
		close(st->pip[num][1]);
		return (0);
	}
	lst = cmds->outfiles;
	while (lst->next)
	{
		if (((t_file *)lst->content)->append == 0)
		{
			temp_fd = open(((t_file *)lst->content)->name, O_WRONLY | O_TRUNC | O_CREAT, 0664);
			if (temp_fd == -1)
				mini_err(st, ERR_SUB_PRCCESS);
			close(temp_fd);
		}
		lst = lst->next;
	}
	if (((t_file *)lst->content)->append == 1)
		temp_fd = open(((t_file *)lst->content)->name, O_WRONLY | O_CREAT | O_APPEND, 0664);
	else
		temp_fd = open(((t_file *)lst->content)->name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (temp_fd == -1)
		mini_err(st, ERR_SUB_PRCCESS);
	if (dup2(temp_fd, 1) == -1)
		mini_err(st, ERR_SUB_PRCCESS);
	return (0);
}

int	pipe_exec_subfunc(t_store *st, t_cmd *cmds, int num)
{
	int	status;

	get_infile_fd(st, cmds, num);
	get_outfile_fd(st, cmds, num);
	st->last_result = execve(st->com[num], st->par[num], st->env);
	if (st->last_result == -1)
		mini_err(st, ERR_FOR_SUBFUNC);
	exit(0);
	return (0);
}

// void test_func(t_store *st, t_cmd *cmds, int num)
// {
// 	printf("fork start :%d\n", num);
// 	// printf("%d) command: %s\n", num, st->com[num]);
// 	// int i = 1;
// 	// while (st->par[num][i])
// 	// {
// 	// 	printf("%d) arg[%d]: %s\n", num, i, st->par[num][i]);
// 	// 	i++;
// 	// }
// }

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
	i = -1;
	while (++i < st->size)
		pid = pipe_exec(st, cmds, i);
	i = -1;
	while (++i < st->size - 1)
	{
		e = -1;
		while (++e < 2)
			close(st->pip[i][e]);
	}
	waitpid(pid, &status, 0);
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
	while (1)
	{
		str = rl_gets();
		if (!str || !*str)
			continue;
		cmds = parser(str, &err);
		if (err)
			continue;
		st.size = get_cmd_size(cmds);
		err = main_loop(&st, cmds);
	}
}
