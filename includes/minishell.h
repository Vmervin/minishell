/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 04:47:31 by vmervin           #+#    #+#             */
/*   Updated: 2022/08/24 13:55:41 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
// # if __linux__
#  include <readline/readline.h>
#  include <readline/history.h>
// # elif _APPLE_
// #  include <editline/readline.h>
// # endif
# include "../libft/libft.h"

enum e_rrors
{
	UNCLOSED = 1,
	NEW_LINE,
	NOFILE,
	NOEXEC,
	CANTOPEN,
	ERR_MALLOC = 1000
};

enum e_type
{
	DEFAULT,
	VARIABLE,
	INPUT
};

enum e_input
{
	HERDOC_EXPAND = 1,
	HERDOC_NOEXPAND = 2
};

// append == 0 (> output, < input)
// append == 1 (>> output, << heredoc)
// append == 2 (<< "heredoc")
typedef struct s_file
{
	char	*name;
	char	*value;
	int		append;
}	t_file;

// output > write in the last, but open all in order
// input < open all, read from last
// vars = split by equl sign on name and value
// command all words not in previous category
typedef struct s_cmd
{
	int		empty;
	t_list	*outfiles;
	t_list	*infiles;
	t_list	*vars;
	t_list	*command;
}	t_cmd;

typedef struct s_token
{
	int	tokentype;
	int	begin;
	int	end;
}	t_token;

typedef struct s_parser
{
	char	*string;
	t_list	*tokens;
	int		error;
}	t_parser;

typedef struct s_info
{
	int		res;
	int		len;
	int		tmpin;
	int		tmpout;
	int		fdin;
	int		fdout;
	int		herdoc;
	char	*hd;
	int		(*fdpipe)[2];
	int		*pid;
	char	*path;
	char	**env;
	char	**args;
	t_cmd	*cmds;
}	t_info;

typedef struct s_global
{
	t_list	*env;
	int		last_exec;
}	t_global;

extern t_global	g_var;

void	rl_replace_line(const char *text, int clear_undo);

// main
char	*rl_gets(void);
int		built_in_check(char *str);
int		is_built_in(t_list *lst, int i, t_info *info);
t_cmd	*parser(char *string, int *error);

// environment
char	*get_var(char *name);
void	change_vars(char *name, char *val);
int		delete_node(t_list **head, char *key);
void	env_to_list(char **env);
char	*get_name(char *str);
char	**list_to_env(void);
char	**list_to_argv(t_list *lst);
void	var_process(t_cmd *simplcmds);

// herdoc
int		heredoc_proc(t_list *lst, t_info *info);

// tokens
void	quote_token_search(t_parser *serv);
int		is_quoted_word(t_list *lst, int i, char type);
void	dollar_sign_token_search(t_list **lst, char type, char *str);
void	one_simbol_token_search(t_list **lst, char type, char *str);
void	space_token_search(t_list **lst, char *type, char *str);
void	word_token_search(t_list **lst, char *str);
void	equal_token_search(t_list **lst, char *str);

// syntax
void	analize_syntax(t_cmd *cmd, t_list *lst, t_parser *service);
t_cmd	*simple_command_parser(t_parser *service);
char	*extractor(char *string, t_parser *service);
void	parse_word(t_list *lst, int vars);
void	remove_empty(t_cmd *cmd, int *error);

// executor
int		init_pipe(t_info *info, int len, t_cmd *cmds);
int		command_executor(t_cmd *cmds, t_info *info, int i);
int		pipe_memfree(t_info info);
int		open_loop(t_cmd cmd, t_info *info);
int		child_birth(t_cmd *cmds, t_info *info, int i);

// built-ins
int		cd(t_list *lst);
int		exit_shell(t_info *info);

// utils
void	add_list(t_list **lst, int begin, int end, char type);
int		add_list_file(t_list **lst, int append, char *name, char *value);
void	memfree(t_list *lst);
void	command_memfree(t_cmd *simplcmds);
char	*ft_strjoin_free(const char *s1, const char *s2);
int		syntax_error(int error);
int		error_mess(char *name, int mode, char *str);
void	lstprint(t_list *lst);
void	lstprint2(t_list *lst);
int		is_strs_equal(char *str1, char *str2);
int		compare_names(void *content1, void *content2);
int		compare_tokens(void *content1, void *content2);
void	ft_list_sort(t_list **begin_list, int (*cmp)());

#endif
