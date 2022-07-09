/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 04:47:31 by vmervin           #+#    #+#             */
/*   Updated: 2022/07/09 22:35:05 by vmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
// #include <string.h>
# include <stdlib.h>
// #include <termios.h>
# include <unistd.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>
// #include <sys/wait.h>
// #include <signal.h>
// #include <dirent.h>
// #include <errno.h>
// #include <sys/ioctl.h>
// #include <curses.h>
// #include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

typedef struct s_file
{
	char	*name;
	char	*value;
	int		append;
}	t_file;

// output > записываем в последний, но открываем или создаем все по порядку
// input <
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

typedef struct s_global
{
	t_list	*env;
	// int error;
}	t_global;

t_global	g_var;

// parser
t_cmd	*parser(char *string, int *error);

// environment
char	*get_var(char *name);
void	remove_vars(char *name);
void	env_to_list(char **env);
char	*get_name(char *str);

// herdoc
void	heredoc(char *eof, int fd, int append);
char	*expand_heredoc(char *string, int append);
int		is_eof(char *line, char *eof);

// tokens
void	add_list(t_list **lst, int begin, int end, char type);
size_t	quote_search(t_parser *service, int i, char type, char *str);
void	quote_token_search(t_parser *serv);
int		is_quoted_word(t_list *lst, int i, char type);
int		is_token(t_list *lst, int i, char type);
int		is_name(t_token *token, int i, char *str);
void	is_word(t_list *lst, int i, char *str);
int		dollar_sign_search(t_list **lst, int i, char type, char *str);
void	dollar_sign_token_search(t_list **lst, char type, char *str);
void	one_simbol_token_search(t_list **lst, char type, char *str);
size_t	many_simbol_search(t_list **lst, int i, char *type, char *str);
void	space_token_search(t_list **lst, char *type, char *str);
size_t	word_search(t_list **lst, int i, char *str);
void	word_token_search(t_list **lst, char *str);
void	equal_token_search(t_list **lst, char *str);
void	grammatic(t_parser *service);

// syntax
int		add_list_file(t_list **lst, int append, char *name, char *value);
t_list	*add_iofile(t_list **cmd, t_list *lst, t_parser *service, char type);
t_list	*skip_space(t_list *lst, t_parser *service, int *append, int type);
t_list	*add_var_declare(t_cmd *cmd, t_list *lst, t_parser *service);
t_list	*add_command(t_cmd *cmd, t_list *lst, t_parser *service);
void	analize_syntax(t_cmd *cmd, t_list *lst, t_parser *service);
int		init_commands(t_cmd *cmd, t_parser *service, int i);
int		search_pipes(t_list *lst);
t_cmd	*simple_command_parser(t_parser *service);
char	*val_search(t_token *token, char *str);
char	**extract_value(t_list *lst, char *str);
char	*ft_strjoin_free(const char *s1, const char *s2);
void	index_plus(t_token *expansion, t_list *tmp, size_t len);
char	*expand_for_real(t_list *lst, char *str, char **val);
char	*remove_quotes(t_list *lst, char *str);
char	*skip_quote(char *newstr, char *str, int *tmp, t_token *tok);
char	*expand(char *string, int herdoc);
void	parse_word(t_list *lst, int vars);
void	pathname_expansion(t_cmd *simpcmds);
void	var_free(t_list *lst);
void	add_vars(t_list *lst);
void	change_vars(char *name, char *val);
void	var_free(t_list *lst);

// utils
void	memfree(t_list *lst);
void	command_memfree(t_cmd *simplcmds);
int		syntax_error(int error);
void	lstprint(t_list *lst);
void	lstprint2(t_list *lst);
int		is_strs_equal(char *str1, char *str2);
int		compare_names(void *content1, void *content2);
int		compare_tokens(void *content1, void *content2);
void	ft_swap_data(t_list *a, t_list *b);
void	ft_list_sort(t_list **begin_list, int (*cmp)());

#endif