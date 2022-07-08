#include "minishell.h"

typedef struct s_store
{
	char	**env;
	char	**path;
}	t_store;

char	*get_path_str(char **env)
{
	if (!env)
		return (NULL);
	while (ft_strncmp(*env, "PATH=", 5))
	{
		// if (!*env)
		// 	err();
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
	st->path = path_separate(env);
	st->env = env;
	if (!st->path)
		return (1);
	return (0);
}

int the_pipe_of_mine(char **commands, char ***params, int **fds_int, int **fds_out)
{
	commands = ft_split("cat grep", ' ');
	params = malloc(sizeof(void *) * 2);
	params[0] = ft_split("-l", ' ');
	params[1] = ft_split("-e", ' ');
	fds_in = malloc(sizeof(int *) * 2);

}

int	main(int args, char **argv, char **env)
{
	t_store	st;
	int	p1[2];
	int fd = open("test_file.txt", O_CREAT);
	char	buf[100];

	if (startup(&st, env))
		return (0);
	pipe(p1);
	int	out = dup(1);
	int fk = fork();
	if (fk == 0)
	{
		printf("out = %d\n", out);
		dup2(p1[1], 1);
		printf("test\n");
		execve("/bin/ls", argv, env);
		int size = read(p1[0], buf, 100);
		write(out, "hello\n", 6);
	}
	else
	{
		printf("im parent\n");
	}
}