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
		if (!*env)
			err();
		env++;
	}
	return (*env + 5);
}

int	path_separate(char **env)
{
	char	*path_str;
	char	**pathes;

	path_str = get_path_str(env);
	if (!path_str)
		return (NULL);
	pathes = ft_split(path_str, ':');
}

int	main(int args, char **argv, char **env)
{

}