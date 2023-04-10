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

NAME		=	a.out
CFLAGS		=	-Wall -Wextra -Werror
LIB42		=	lib42
LIBFLAGS	+=	-lreadline
LIBFLAGS	+=	-Llib42 -lft
# LIBFLAGS	+=	-L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include
SANITIZE	=	-fsanitize=address -g3

FILES		=	main
SRCS		=	$(addsuffix, .c, FILES)

all:
	make -C lib42
	gcc $(CFLAGS) main.c $(LIBFLAGS) && ./a.out

clean:
	make clean -C lib42
	$(RM) *.o

fclean:	clean
	make fclean -C lib42
	$(RM) $(NAME)

re:	fclean all