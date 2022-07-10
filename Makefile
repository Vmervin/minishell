# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmervin <vmervin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/23 17:20:35 by vmervin           #+#    #+#              #
#    Updated: 2022/07/10 17:00:41 by vmervin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell
SRC_DIR		= ./src/
SRCS		= ${addprefix ${SRC_DIR}, ${UTILS} ${PARSER}}
UTILS_DIR	= utils/
UTILS		= ${addprefix ${UTILS_DIR}, command_memfree.c errors.c \
ft_lst_sort.c}
PARSER_DIR	= parser/
PARSER		= ${addprefix ${PARSER_DIR}, add_list_file.c \
command_parser.c dollar_token.c equal_token.c parser.c pathname_expansion.c \
quote_token.c space_redirect_token.c var_expansion.c word_token.c}
HEADERS		= ${INCLUDES}/minishell.h
LIBFTPATH	= ./libft
LIBFT		= ${LIBFTPATH}/libft.a
INCLUDES 	= ./includes
OBJECTS		= ${addprefix ${OBJ_DIR}, ${patsubst %.c,%.o,${notdir ${SRCS}}}}
OBJ_DIR		= ./obj/
D_FILES		= ${patsubst %.o,%.d,${OBJECTS}}
CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror -I${INCLUDES}
CFLAGS2		= -L${LIBFTPATH} -lft -L~/.brew/Cellar/readline/8.1.2/lib/ -I~/.brew/Cellar/readline/8.1.2/include
RM 			= rm -f

all:		$(NAME)

${NAME}:	${OBJECTS} ${LIBFT}
			${CC} ${CFLAGS} ${OBJECTS} ${CFLAGS2} -o $@

${LIBFT}::
			${MAKE} -C ${LIBFTPATH}

${OBJ_DIR}%.o:	${SRC_DIR}%.c ${HEADERS} | ${OBJ_DIR}
			${CC} ${CFLAGS} -c $< ${CFLAGS2} -o $@

${OBJ_DIR}%.o:	${SRC_DIR}${UTILS_DIR}%.c ${HEADERS} | ${OBJ_DIR}
			${CC} ${CFLAGS} -c $< ${CFLAGS2} -o $@

clean:	
			${RM} ${OBJECTS} ${D_FILES}
			${MAKE} clean -C ${LIBFTPATH}

fclean:		clean
			${RM} ${NAME}
			${RM} ${LIBFT}

re:			fclean all

.PHONY: clean fclean all re bonus
