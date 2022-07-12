# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/23 17:20:35 by vmervin           #+#    #+#              #
#    Updated: 2022/07/12 07:24:36 by vmervin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell
SRC_DIR		= ./srcs/
SRCS		= ${addprefix ${SRC_DIR}, built-ins.c environ.c	errors.c \
ft_lst_sort2.c	main.c	command_memfree.c ft_lst_sort.c	heredoc_proc.c \
prompt.c var_process.c built-ins2.c ${PARSER}}
PARSER_DIR	= parser/
PARSER		= ${addprefix ${PARSER_DIR}, add_list_file.c \
command_parser.c dollar_token.c equal_token.c parser.c pathname_expansion.c \
quote_token.c space_redirect_token.c var_expansion.c word_token.c \
expansion_empty.c}
HEADERS		= ${INCLUDES}/minishell.h
LIBFTPATH	= ./libft
LIBFT		= ${LIBFTPATH}/libft.a
INCLUDES 	= ./includes
OBJECTS		= ${addprefix ${OBJ_DIR}, ${patsubst %.c,%.o,${notdir ${SRCS}}}}
OBJ_DIR		= ./obj/
D_FILES		= ${patsubst %.o,%.d,${OBJECTS}}
CC 			= cc
CFLAGS		= -Wall -Wextra -I${INCLUDES} -MD
#CFLAGS2		= -L${LIBFTPATH} -lft -L${READLINE}lib -I${READLINE}include -lreadline # flags for macOS with homebrew
#CFLAGS2		= -L${LIBFTPATH} -lft 
CFLAGS2		= -L${LIBFTPATH} -lft -lncurses -lreadline # flags for linux (do not delete, comment instead)
READLINE	= /opt/homebrew/Cellar/readline/8.1.2/
RM 			= rm -f

all:		$(NAME)

${NAME}:	${OBJECTS} ${LIBFT}
			${CC} ${CFLAGS} ${OBJECTS} ${CFLAGS2} -o $@

${LIBFT}::
			${MAKE} -C ${LIBFTPATH}

${OBJ_DIR}%.o:	${SRC_DIR}%.c ${HEADERS} | ${OBJ_DIR}
			${CC} ${CFLAGS} -c $< ${CFLAGS2} -o $@

${OBJ_DIR}%.o:	${SRC_DIR}${PARSER_DIR}%.c ${HEADERS} | ${OBJ_DIR}
			${CC} ${CFLAGS} -c $< ${CFLAGS2} -o $@

${OBJ_DIR}: 
			mkdir ${OBJ_DIR}

clean:	
			${RM} ${OBJECTS} ${D_FILES}
			${MAKE} clean -C ${LIBFTPATH}

fclean:		clean
			${RM} ${NAME}
			${RM} ${LIBFT}

re:			fclean all

.PHONY: clean fclean all re bonus
