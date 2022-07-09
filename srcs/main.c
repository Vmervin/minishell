#include "../includes/minishell.h"

// void	free_appropriate_struct(t_store *st)
// {
	
// }

t_global g_var;

int	mini_err(t_store *st, int err)
{
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

	st->path = path_separate(env);
	st->env = env;
	if (!st->path)
		return (1);
	return (0);
	st->com = NULL;
	st->par = NULL;
}

// int the_pipe_of_mine(char **commands, char ***params, int **fds_int, int **fds_out)
// {
// 	commands = ft_split("cat grep", ' ');
// 	params = malloc(sizeof(void *) * 2);
// 	params[0] = ft_split("-l", ' ');
// 	params[1] = ft_split("-e", ' ');
// 	fds_in = malloc(sizeof(int *) * 2);

// }

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
		st->pip = mini_calloc(2, sizeof(int), st);
		st->par = mini_calloc(get_list_size(cmds->command), sizeof(void *), st);
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
		st->com[i] = (char *)(cmds->command->content);
		e = -1;
		curlist = cmds->command->next;
		while (cmds->command)
		{
			st->par[i][++e] = (char *)(cmds->command->content);
			curlist = curlist->next;
		}
		st->com[i][e] = '\n';
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
		if (dup2(st->pip[num - 1][0], 0))
			mini_err(st, ERR_SUB_PRCCESS);
		return (0);
		// temp_fd = open(((t_file *)cmds->infiles->content), O_RDONLY);
		// if (dup2(temp_fd, 0) == -1)
		// 	mini_err(st, ERR_SUB_PRCCESS);
		// return (0);
	}
	lst = cmds->infiles;
	while (lst->next)
		lst = lst->next;
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
		if (dup2(st->pip[num][1], 1))
			mini_err(st, ERR_SUB_PRCCESS);
		return (0);
		// temp_fd = open(((t_file *)lst->content)->name, O_RDWR | O_TRUNC);
		// if (temp_fd == -1)
		// 	mini_err(st, ERR_SUB_PRCCESS);
	}
	lst = cmds->outfiles;
	while (lst->next)
	{
		if (((t_file *)lst->content)->append == 1)
		{
			temp_fd = open(((t_file *)lst->content)->name, O_RDWR | O_TRUNC);
			if (temp_fd == -1)
				mini_err(st, ERR_SUB_PRCCESS);
			close(temp_fd);
		}
		lst = lst->next;
	}
	temp_fd = open(((t_file *)lst->content)->name, O_WRONLY);
	if (temp_fd == -1)
		mini_err(st, ERR_SUB_PRCCESS);
	if (dup2(temp_fd, 1) == -1)
		mini_err(st, ERR_SUB_PRCCESS);
	return (0);
}

		// if (((t_file *)cmds->infiles->content)->append)
int	pipe_exec_subfunc(t_store *st, t_cmd *cmds, int num)
{
	int	status;

	get_infile_fd(st, cmds, num);
	get_outfile_fd(st, cmds, num);
	st->last_result = execve(st->com[num], st->par[num], st->env);
	if (st->last_result == -1)
		mini_err(st, ERR_FOR_SUBFUNC);
	return (0);
}

int	pipe_exec(t_store *st, t_cmd *cmds, int num)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid < 0)
		mini_err(st, ERR_FORK_INIT);
	if (pid == 0)
	{
		waitpid(pid, &status, 0);
		status = WEXITSTATUS(status);
		if (status)
			mini_err(st, ERR_SUB_PRCCESS);
	}
	if (pid != 0)
	{
		pipe_exec_subfunc(st, cmds, num);
	}
	return (0);
}

int	main_loop(t_store *st, t_cmd *cmds)
{
	int	i;

	malloc_appropriate_struct(st, cmds);
	create_appropriate_struct(st, cmds);
	i = -1;
	while (++i < st->size)
		pipe_exec(st, cmds, i);
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
		str = readline("minishell>");
		if (!str)
			continue;
		cmds = parser(str, &err);
		if (err)
			continue;
		st.size = 0;
		err = main_loop(&st, cmds);
	}
}
	// int	p1[2];
	// int fd = open("test_file.txt", O_CREAT);
	// char	buf[100];

	// pipe(p1);
	// int	out = dup(1);
	// int fk = fork();
	// if (fk == 0)
	// {
	// 	printf("out = %d\n", out);
	// 	dup2(p1[1], 1);
	// 	printf("test\n");
	// 	execve("/bin/ls", argv, env);
	// 	int size = read(p1[0], buf, 100);
	// 	write(out, "hello\n", 6);
	// }
	// else
	// {
	// 	printf("im parent\n");
	// }