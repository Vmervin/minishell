#include "../includes/minishell.h"

char	*prompt_invitation(void)
{
	char	*prompt;

	prompt = ft_strjoin("[", get_var("USER"));
	prompt = ft_strjoin_free(prompt, ft_strdup("@"));
	prompt = ft_strjoin_free(prompt, ft_strdup(get_var("HOSTNAME")));
	// prompt = ft_strjoin_free(prompt, ft_strdup("	"));
	// prompt = ft_strjoin_free(prompt, ft_strdup(get_var("PWD")));
	prompt = ft_strjoin_free(prompt, ft_strdup("]$ "));
	return (prompt);
}

char	*rl_gets(void)
{
	char	*line;
	char	*prompt;

	prompt = prompt_invitation();
	line = readline(prompt);
	free(prompt);
	if (line)
		add_history(line);
	return (line);
}