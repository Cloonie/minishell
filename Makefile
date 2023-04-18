# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/08 17:01:05 by mliew             #+#    #+#              #
#    Updated: 2023/04/08 17:01:05 by mliew            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CFLAGS		=	-Wall -Wextra -Werror
CC			=	gcc
LIB42		=	lib42
LIBFLAGS	+=	-lreadline
LIBFLAGS	+=	-Llib42 -lft
# LIBFLAGS	+=	-L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include
SANITIZE	=	-fsanitize=address -g3

FILES		=	main build_ins
SRCS		=	$(addsuffix .c, $(FILES))
OBJS		=	$(addsuffix .o, $(FILES))

all: $(OBJS)
	make -C lib42
	# gcc $(CFLAGS) $(SRCS) -c
	gcc $(CFLAGS) $(SRCS) $(LIBFLAGS) -o $(NAME) && ./$(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C lib42
	$(RM) *.o

fclean:	clean
	make fclean -C lib42
	$(RM) $(NAME)

re:	fclean all