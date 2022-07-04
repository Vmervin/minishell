# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmervin <vmervin@student-21.school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/23 00:37:28 by vmervin           #+#    #+#              #
#    Updated: 2022/06/26 11:31:58 by vmervin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= libft.a
SRC_DIR		= ./src/
INCLUDES 	= ./includes/
OBJ_DIR		= ./obj/
SRCS 		= ${addprefix ${SRC_DIR}, ft_atoi.c ft_bzero.c ft_calloc.c\
 ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c\
 ft_itoa.c ft_memcpy.c ft_memmove.c ft_memset.c ft_memchr.c\
 ft_memcmp.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strchr.c\
 ft_strrchr.c ft_strncmp.c ft_strnstr.c ft_strdup.c ft_substr.c\
 ft_strjoin.c ft_strtrim.c ft_split.c ft_strmapi.c ft_striteri.c\
 ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
 ft_tolower.c ft_toupper.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c\
 ft_lstlast.c ft_lstnew.c ft_lstsize.c ft_lstadd_back.c}
SRCS_GNL	= ${addprefix ${SRC_DIR}, get_next_line.c get_next_line_utils.c}
SRCS_PRINTF	= ${addprefix ${SRC_DIR}, ft_printf.c ft_printf_utils.c}
HEADERS		= ${addprefix ${INCLUDES}, ft_printf.h get_next_line.h} libft.h
OBJECTS		= ${addprefix ${OBJ_DIR}, ${patsubst %.c,%.o,${notdir ${SRCS}\
${SRCS_GNL} ${SRCS_PRINTF}}}}
D_FILES		= ${patsubst %.o,%.d,${OBJECTS}}
CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror -I${INCLUDES} -MD
ARRC 		= ar rc
MKDIR		= mkdir -p
RM 			= rm -f
VPATH		= src/:includes/

.PHONY: clean fclean all re bonus libftprintf libgnl libft

all : 		$(NAME)

${NAME}:	${OBJECTS}
			${ARRC} ${NAME} $?

#${OBJ_DIR}%.o:	%.c
#			${CC} ${CFLAGS} -c $< -o ${OBJ_DIR}${notdir $@}

${OBJ_DIR}%.o:	${SRC_DIR}%.c ${HEADERS}
			${MKDIR} ${OBJ_DIR}
			${CC} ${CFLAGS} -c $< -o ${OBJ_DIR}${notdir $@}

include ${wildcard ${D_FILES}}

clean:	
			${RM} ${OBJECTS} ${D_FILES}

fclean:		clean
			${RM} ${NAME}

re:			fclean all
