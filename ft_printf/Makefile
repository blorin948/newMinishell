# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/16 14:41:03 by blorin            #+#    #+#              #
#    Updated: 2020/12/15 18:25:19 by blorin           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SRC = check_flags2.c\
	convert_c.c\
	convert_hexa.c\
	convert_p.c\
	convert_pourcent.c\
	convert_s.c\
	convert_type_x.c\
	convert_u_d.c\
	convert_x.c\
	flags_pourcent.c\
	ft_printf.c\
	ftc1.c\
	ftc2.c\
	parse.c\
	check_flags.c\
	write_flags.c\
	putnbr.c\

OBJS = ${SRC:.c=.o}

OBJBS = ${SRCB:.c=.o} ${SRC:.c=.o}

NAME = libftprintf.a

RM = rm -f

CC = gcc

HEADERS = ft_printf.h

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
