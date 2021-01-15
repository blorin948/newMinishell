# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/16 14:30:22 by blorin            #+#    #+#              #
#    Updated: 2020/12/14 19:23:26 by blorin           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SRC =	ft_atoi.c\
		ft_bzero.c\
		ft_calloc.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isprint.c\
		ft_itoa.c\
		ft_memccpy.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_memset.c\
		ft_putchar_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_putstr_fd.c\
		ft_split.c\
		ft_strchr.c\
		ft_strdup.c\
		ft_strjoin.c\
		ft_strlcat.c\
		ft_strlcpy.c\
		ft_strlen.c\
		ft_strmapi.c\
		ft_strncmp.c\
		ft_strnstr.c\
		ft_strrchr.c\
		ft_strtrim.c\
		ft_substr.c\
		ft_tolower.c\
		ft_toupper.c\

SRCB = 	ft_lstnew_bonus.c\
		ft_lstadd_front_bonus.c\
		ft_lstsize_bonus.c\
		ft_lstlast_bonus.c\
		ft_lstadd_back_bonus.c\
		ft_lstdelone_bonus.c\
		ft_lstclear_bonus.c\
		ft_lstiter_bonus.c\

OBJS = ${SRC:.c=.o}

OBJBS = ${SRCB:.c=.o} ${SRC:.c=.o}

NAME = libft.a

RM = rm -f

CC = gcc

HEADERS = libft.h

CFLAGS = -o -Wall -Wextra -Werror

all:	${NAME}

$(OBJS): ${HEADERS}

$(OBJBS): ${HEADERS}

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
		ar rc ${NAME} ${OBJS}
		ranlib ${NAME}

bonus:		${OBJS} ${OBJBS}
		ar rc ${NAME} ${OBJBS}
		ranlib ${NAME}

fclean:		clean
			${RM} ${NAME}

clean:
		${RM} *.o

re: fclean all

.PHONY:		all clean fclean re
