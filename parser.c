#include <stdio.h>
// #include <string.h>
#include <stdlib.h>
// #include <termios.h>
#include <unistd.h>
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
// #include <readline/readline.h>
// #include <readline/history.h>
#include "./libft/libft.h"

typedef struct	s_file
{
	char	*name;
	char	*value;
	int		append;	
}	t_file;

typedef	struct	s_cmd
{
	char 	**args;
	char	*substr;
	int		delim;
	int		empty;
	t_list *outfiles;
	t_list *infiles;
	t_list *vars;
	t_list *command; 
}	t_cmd;

typedef struct s_token
{
	int tokentype;
	int begin;
	int end;
}	t_token;

void	lstprint(t_list *lst)
{
	while (lst->next)
	{
		ft_printf("list= %d ", ((t_token *)lst->content)->begin);
		ft_printf("%d ", ((t_token *)lst->content)->end);
		ft_printf("%c\n", ((t_token *)lst->content)->tokentype);
		lst = lst->next;
	}
	ft_printf("list = %d ", ((t_token *)lst->content)->begin);
	ft_printf("%d ", ((t_token *)lst->content)->end);
	ft_printf("%c\n", ((t_token *)lst->content)->tokentype);
}

int compare_tokens(void *content1, void *content2)
{
	return (((t_token *)content1)->begin > ((t_token *)content2)->begin);
}

void	ft_swap_data(t_list *a, t_list *b)
{
	t_list tmp;

	tmp.content = a->content;
	a->content = b->content;
	b->content = tmp.content;
}

void	ft_list_sort(t_list **begin_list, int (*cmp)())
{
	t_list *current;

	if (*begin_list || (*begin_list)->content)
	{
		current = *begin_list;
		while (current->next)
		{
			if ((*cmp)(current->content, current->next->content) > 0)
			{
				ft_swap_data(current, current->next);
				current = *begin_list;
			}
			else
				current = current->next;
		}
	}
}

void	add_list(t_list **lst, int begin, int end, char type)
{
	t_token	*content;

	content = malloc(sizeof(t_token));
	content->begin = begin;
	content->end = end;
	content->tokentype = (int)type;
	ft_lstadd_back(lst, ft_lstnew(content));
}

void	add_list_file(t_list **lst, int append, char *name, char *value)
{
	t_file	*content;

	content = malloc(sizeof(t_file));
	content->append = append;
	content->name = name;
	content->value = value;
	ft_lstadd_back(lst, ft_lstnew(content));
}

size_t quote_search(t_list **lst, int i, char type, char *str)
{
	int tmp_begin;

	tmp_begin = -1;
	if (!str[i])
		return (++i);
	while (str[i] && str[i] != type)
		i++;
	if (str[i] && str[i] == type)
		tmp_begin = i;
	i++;
	while (str[i] && str[i] != type)
		i++;
	if (str[i] && str[i] == type && tmp_begin >= 0)
		add_list(lst, tmp_begin, i, type);
	if (tmp_begin > 0 && !str[i])
		perror("Error: Unclosed quotes\n");// освобождение памяти и завершение обработки команды
	return (++i);
	// сообщение об ошибке если начало есть а конца нет
}

void	quote_token_search(t_list **lst, char type, char *str)
{
	int i;
	int len;
	int quotes[2];

	i = 0;
	len = ft_strlen(str);
	quotes[0] = '\'';
	quotes[1] = '\"';
	while (i <= len)
	{
		i = quote_search(lst, i, quotes[!(ft_strchr(str, '\'') < ft_strchr(str, '\"'))], str);
		i = quote_search(lst, i, quotes[(ft_strchr(str, '\'') < ft_strchr(str, '\"'))], str);
	}
}

int is_quoted_word(t_list *lst, int i, char type)
{
	while (lst)
	{
		if (type != '$' && ((t_token *)lst->content)->tokentype == '\"')
		{
			if (i >= ((t_token *)lst->content)->begin 
				&& i <= ((t_token *)lst->content)->end)
				return (2);
		}
		if (((t_token *)lst->content)->tokentype == '\'')
		{
			if (i >= ((t_token *)lst->content)->begin 
				&& i <= ((t_token *)lst->content)->end)
				return (1);
		}
		lst = lst->next;
	}
	return (0);
}

int is_token(t_list *lst, int i, char type)
{// type можно поменять на флажок
	while (lst)
	{
		if (i >= ((t_token *)lst->content)->begin 
			&& i <= ((t_token *)lst->content)->end)
		{
			if (type != '$')
				return (1);
			else
			{
				if (((t_token *)lst->content)->tokentype != '\"')
					return (2);
			}
		}
		lst = lst->next;
	}
	return (0);
}

int is_name(t_token *token, int i, char *str)
{
	int j;

	j = token->begin;
	if (!ft_isalpha(str[j]) && str[j] != '_')
		return (0);
	while (j < i)
	{
		if (!ft_isalnum(str[j]) && str[j] != '_')
			return (0);
		j++;
	}
	return (1);
}

void is_word(t_list *lst, int i, char *str)
{// меняет тип токена с w на = и конец токена там же где =
	while (lst)
	{
		if (i >= ((t_token *)lst->content)->begin 
			&& i <= ((t_token *)lst->content)->end)
		{
			if (((t_token *)lst->content)->tokentype == 'w')
			{
				if (((t_token *)lst->content)->begin != i 
					&& is_name(((t_token *)lst->content), i, str))
				{
					((t_token *)lst->content)->tokentype = '=';
					((t_token *)lst->content)->end = i;
				}
			}
		}
		lst = lst->next;
	}
}

int	dollar_sign_search(t_list **lst, int i, char type, char *str)
{// аргумент type лишний, можно заменить на $
	int tmp_begin;

	tmp_begin = -1;
	if (!str[i])
		return (++i);
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] == '$' && !is_quoted_word(*lst, i, type))
		tmp_begin = i;
	i++;
	if (str[i] && ft_strchr("\n\t ", str[i]))
		return (i);
	while (str[i] && !is_token(*lst, i, type) && !ft_strchr("\n\t ", str[i]))
		i++;
	i--;
	if (str[i] && tmp_begin >= 0)
		add_list(lst, tmp_begin, i, '$');
	return (i += 2);
}

void	dollar_sign_token_search(t_list **lst, char type, char *str)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(str);
	while (i <= len)
		i = dollar_sign_search(lst, i, type, str);
}

void	one_simbol_token_search(t_list **lst, char type, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == type && !is_quoted_word(*lst, i, type))
			add_list(lst, i, i, type);
		i++;
	}
}

size_t	many_simbol_search(t_list **lst, int i, char *type, char *str)
{	//шесть пробелов - это шесть токенов-разделителей, или один большой токен-разделитель? нужно смотреть стандарт
	int tmp_begin;

	tmp_begin = -1;
	if (!str[i])
		return (++i);
	while (str[i] && !ft_strchr(type, str[i]))
		i++;
	while (str[i] && ft_strchr(type, str[i]) && !is_quoted_word(*lst, i, type[0]))
	{
		if (tmp_begin < 0)
			tmp_begin = i;
		i++;
	}
	i--;
	if (str[i] && tmp_begin >= 0)
		add_list(lst, tmp_begin, i, ' ');
	return (i += 2);
}

void	space_token_search(t_list **lst, char *type, char *str)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(str);
	while (i <= len)
		i = many_simbol_search(lst, i, type, str);
}

size_t	word_search(t_list **lst, int i, char *str)
{// применять последним, чтобы все остальное уже было в токенах
	int tmp_begin;

	tmp_begin = -1;
	if (!str[i])
		return (++i);
	while (str[i] && !is_token(*lst, i, 0))
	{
		if (tmp_begin < 0)
			tmp_begin = i;
		i++;
	}
	i--;
	if (str[i] && tmp_begin >= 0)
		add_list(lst, tmp_begin, i, 'w');
	return (i += 2);
}

void	word_token_search(t_list **lst, char *str)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(str);
	while (i <= len)
		i = word_search(lst, i, str);
}

void equal_token_search(t_list **lst, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			is_word(*lst, i, str);
		i++;
	}
	// если появилось присваивание, то после него неважно что.
	// может и ничего не быть, переменная создастся с пустым значением
	// то есть можно создать присваивание от начала имени и до знака равно
	// а затем прибавлять все токены типа слово и кавычки 
	// поэтому искать знаки = лучше после сортировки токенов
	// а значение присваивать можно только после убирания кавычек 
}

void syntax_error(int c)
{
	ft_putstr_fd("Syntax error near unexpected token '", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
}

t_list *add_outfile(t_cmd *cmd, t_list *lst, char *str)
{
	int begin;
	int end;
	int append;

	append = 0;
	if (((t_token *)lst->content)->tokentype == '>')
	{
		append = 1;
		lst = lst->next;
	}
	while (lst && ((t_token *)lst->content)->tokentype == ' ')
		lst = lst->next;
	if (ft_strchr(">|<", ((t_token *)lst->content)->tokentype))
		syntax_error(((t_token *)lst->content)->tokentype);
	begin = ((t_token *)lst->content)->begin;
	end = ((t_token *)lst->content)->end;
	while (lst && ft_strchr("w$\'\"=", ((t_token *)lst->content)->tokentype))
	{
		if (end < ((t_token *)lst->content)->end)
			end = ((t_token *)lst->content)->end;
		lst = lst->next;
	}
	add_list_file(&cmd->outfiles, append, ft_substr(str, begin, end - begin + 1), NULL);
	return (lst);
}

t_list *add_infile(t_cmd *cmd, t_list *lst, char *str)
{
	int begin;
	int end;

	if (((t_token *)lst->content)->tokentype == '<')
	{
		// here_doc это совсем другая история
		lst = lst->next;
	}
	while (lst && ((t_token *)lst->content)->tokentype == ' ')
		lst = lst->next;
	if (ft_strchr(">|<", ((t_token *)lst->content)->tokentype))
		syntax_error(((t_token *)lst->content)->tokentype);
	begin = ((t_token *)lst->content)->begin;
	end = ((t_token *)lst->content)->end;
	while (lst && ft_strchr("w$\'\"=", ((t_token *)lst->content)->tokentype))
	{
		if (end < ((t_token *)lst->content)->end)
			end = ((t_token *)lst->content)->end;
		lst = lst->next;
	}
	add_list_file(&cmd->infiles, 0, ft_substr(str, begin, end - begin + 1), NULL);
	return (lst);
}

t_list *add_var_declare(t_cmd *cmd, t_list *lst, char *str)
{
	int begin;
	int end;
	char *name;

	begin = ((t_token *)lst->content)->begin;
	end = ((t_token *)lst->content)->end;
	name = ft_substr(str, begin, end - begin);
	begin = end + 1;
	lst = lst->next;
	while (lst && ft_strchr("w$\'\"=", ((t_token *)lst->content)->tokentype))
	{
		if (end < ((t_token *)lst->content)->end)
			end = ((t_token *)lst->content)->end;
		lst = lst->next;
	}
	add_list_file(&cmd->vars, 0, name, ft_substr(str, begin, end - begin + 1));
	return (lst);
}

t_list *add_command(t_cmd *cmd, t_list *lst, char *str)
{
	int begin;
	int end;

	begin = ((t_token *)lst->content)->begin;
	end = ((t_token *)lst->content)->end;
	while (lst && ft_strchr("w$\'\"=", ((t_token *)lst->content)->tokentype))
	{
		if (end < ((t_token *)lst->content)->end)
			end = ((t_token *)lst->content)->end;
		lst = lst->next;
	}
	add_list_file(&cmd->command, 0, ft_substr(str, begin, end - begin + 1), NULL);
	cmd->delim = 1;
	return (lst);
}

void analize_syntax(t_cmd *cmd, t_list *lst, char *str)
{
	int x;

	x = 0;
	while (lst && ((t_token *)lst->content)->tokentype != '|')
	{
		printf("token: from %d to %d type of '%c'\n",((t_token *)lst->content)->begin,
		 		((t_token *)lst->content)->end, ((t_token *)lst->content)->tokentype);
		// имена файлов для редиректа
		if (((t_token *)lst->content)->tokentype == '>')
			lst = add_outfile(cmd, lst->next, str);
		else if (((t_token *)lst->content)->tokentype == '<')
			lst = add_infile(cmd, lst->next, str);
		// присвоения переменных
		else if (!x && ((t_token *)lst->content)->tokentype == '=')
			lst = add_var_declare(cmd, lst, str);
		// все остальное является командой и ее аргументами
		else if (((t_token *)lst->content)->tokentype != ' ')
		{	
			lst = add_command(cmd, lst, str);// впоследствии можно убрать флажок и использовать 
			x = 1;// delim из структуры t_cmd если места не будет хватать
		}
		else
			lst = lst->next;
		if (lst)
			printf("token after: from %d to %d type of '%c'\n",((t_token *)lst->content)->begin,
			 		((t_token *)lst->content)->end, ((t_token *)lst->content)->tokentype);
	}
	if (cmd->outfiles)
		printf("\nout name %s\n", ((t_file *)cmd->outfiles->content)->name);
	if (cmd->infiles)
		printf("\nin name %s\n", ((t_file *)cmd->infiles->content)->name);
	if (cmd->vars)
		printf("\nvar name %s =value %s\n", ((t_file *)cmd->vars->content)->name, 
				((t_file *)cmd->vars->content)->value);
	if (cmd->command)
		printf("\ncommand name %s\n", ((t_file *)cmd->command->content)->name);
}

int init_commands(t_cmd *cmd, t_list *lst, char *str, int i)
{
	cmd->outfiles = NULL;
	cmd->infiles = NULL;
	cmd->vars = NULL;
	cmd->command = NULL;
	cmd->delim = 0;
	cmd->empty = 0;// используется для определения конца списка пайпов. можно
	if (!lst && !str) // было делать проверку на одновременное отсутствие vars и command,
		cmd->empty = 1; // но это может быть либо конец либо синтаксическая ошибка
	while (lst && (i > 0))
	{
		if (((t_token *)lst->content)->tokentype == '|')
			i--;
		lst = lst->next;
	}// здесь желательно чтобы i кончилось раньше чем кончится список, 
	// иначе нечего будет обработать

	// просто проанализировать каждый токен
	analize_syntax(cmd, lst, str);
	return (0);
}

int search_pipes(t_list *lst)
{
	int count;

	count = 0;
	while (lst->next)
	{
		if (((t_token *)lst->content)->tokentype == '|')
			count++;
		lst = lst->next;
	}
	return (count);
}

t_cmd *simple_command_parser(t_list *lst, char *str)
{
	int count;
	t_cmd *scmds;
	int i;

	count = 0;
	count = search_pipes(lst) + 1;
	scmds = malloc(sizeof(t_cmd) * (count + 1));
	i = 0;
	while (i < count)
	{
		printf("%d\n", i+1);
		init_commands(&scmds[i], lst, str, i);
		i++;
	}
	init_commands(&scmds[i], NULL, NULL, i);
	return (scmds);
}

// char *expand_for_real(t_list *lst, char *str)
// {
// 	int begin;
// 	int end;
// 	char *newstr;

// 	while (lst)
// 	{
// 		if (((t_token *)lst->content)->tokentype == '$')
// 			ft_substr(str, begin, end - begin + 1);
// 		ft_strnstr();// нужно найти слово, найти для него замену,
// 		//  потом убрать кавычки, и в конце найти слово еще раз и заменить
// 		// вот только это не сработает в случае с '$USER'$USER
// 		// то же самое будет и если сначала убрать кавычки
// 		// нужно джойнить куски старой строки в новую по очереди,
// 		// пропускать кавычки, проверяя индекс в старой строке,
// 		// джойнить значение переменной и плюсовать индекс на длину имени переменной,
// 		// индекс должен быть только один в старой строке, а новая добавляется вслепую
// 		// str2 = substr(0, begin), strjoin(res, str2), free(str2), str2 = substr(begin+1, end-1)
// 		// 
// 		ft_strtrim();
// 		lst = lst->next;
// 	}
// 	free(str);
// 	return (newstr);
// }

void expand(char *string)
{
	t_list *tokens;

	tokens = NULL;
	if (ft_strchr(string, '\'') || ft_strchr(string, '\"'
		|| ft_strchr(string, '$')))
	{
		quote_token_search(&tokens, '\"', string);
		dollar_sign_token_search(&tokens, '$', string);
		ft_list_sort(&tokens, compare_tokens);
		// string = expand_for_real(tokens, string);
		// ft_lstclear(&tokens, ft_lstdelone);
	}
}

void parse_word(t_list *lst, int vars)
{
	while (lst)
	{
		if (vars)
			expand(((t_file *)(lst->content))->value);
		else
			expand(((t_file *)(lst->content))->name);
		lst = lst->next;
	}
}

void pathname_expansion(t_cmd *simpcmds)
{
	int i;
	i = 0;
	while (!simpcmds[i].empty)
	{
		// по очереди смотреть все списки, искать для каждой строки кавычки, $, все заменять,
		// старые строки освобождать, новые создавать
		// 
		parse_word(simpcmds->infiles, 0);
		parse_word(simpcmds->outfiles, 0);
		parse_word(simpcmds->command, 0);
		parse_word(simpcmds->vars, 1);
		i++;
	}
}

int main (void)
{
	char *string;
	t_list *tokens;
	t_cmd *simplcmds;

	tokens = NULL;
	// string = "echo \" $ $eskeetit  \" | grep \'\"|kek\"\' | wc -l > \" \'Proctor&Gamble\'\"";
	string = "< hhhh ec'ho\" d\"dd=dd=$eskeetit | grep kek | wc -l > Proctor&Gamble";
	quote_token_search(&tokens, '\"', string);
	one_simbol_token_search(&tokens, '|', string);
	one_simbol_token_search(&tokens, '>', string);
	one_simbol_token_search(&tokens, '<', string);
	many_simbol_token_search(&tokens, "\t\n ", string);
	word_token_search(&tokens, string);
	// знаки "=" имеют смысл только в словах и только если перед знаком "=" стоит ИМЯ
	equal_token_search(&tokens, string);
	word_token_search(&tokens, string);
	ft_list_sort(&tokens, compare_tokens);
	// модуль синтаксического анализа
// /* 
	simplcmds = simple_command_parser(tokens, string);
// */
	// следующие действия уже после группировки токенов и синтаксического анализа
	// field_spliting();// не нужно, они уже и так разделены
	// pathname_expansion(simplcmds);
	// в присвоениях и перенаправлениях раскрытие $ происходит тоже
	// quote_removal();
	lstprint(tokens);
	printf("\n%s\n", ((t_file *)simplcmds[2].outfiles->content)->name);
	printf("\n%s\n", ((t_file *)simplcmds[0].command->next->content)->name);
	return (0);
}
