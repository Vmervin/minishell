# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmervin <vmervin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/23 17:20:35 by vmervin           #+#    #+#              #
#    Updated: 2022/07/10 18:04:13 by vmervin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell
SRC_DIR		= ./srcs/
SRCS		= ${addprefix ${SRC_DIR}, add_list_file.c command_parser.c	environ.c	errors.c \
ft_lst_sort2.c	main.c	pathname_expansion.c quote_token.c	var_expansion.c	word_token.c \
command_memfree.c	dollar_token.c	equal_token.c	ft_lst_sort.c	heredoc_proc.c	parser.c \
prompt.c	space_redirect_token.c	var_process.c}
HEADERS		= ${INCLUDES}/minishell.h
LIBFTPATH	= ./libft
LIBFT		= ${LIBFTPATH}/libft.a
INCLUDES 	= ./includes
OBJECTS		= ${SRCS:.c=.o}
CC 			= cc
CFLAGS		= -Wall -Wextra -I${INCLUDES}
CFLAGS2		= -L${LIBFTPATH} -lft -L~/.brew/Cellar/readline/8.1.2/lib/ -I~/.brew/Cellar/readline/8.1.2/include -lreadline
RM 			= rm -f

all:		$(NAME)

${NAME}:	${OBJECTS} ${LIBFT}
			${CC} ${CFLAGS} ${OBJECTS} ${CFLAGS2} -o $@

${LIBFT}::
			${MAKE} -C ${LIBFTPATH}

${OBJECTS}:	Makefile

clean:	
			${RM} ${OBJECTS} ${D_FILES}
			${MAKE} clean -C ${LIBFTPATH}

fclean:		clean
			${RM} ${NAME}
			${RM} ${LIBFT}

re:			fclean all

.PHONY: clean fclean all re bonus
