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

B_GREEN=	\033[38;5;121m
B_RED	=	\033[38;5;204m
C_GREEN	=	\033[0;32m
C_RED	=	\033[0;31m
C_BLUE	=	\033[0;34m
C_END 	=	\033[0m
C_ENDR	=	\033[0m\r

NAME		=	minishell
CFLAGS		=	-Wall -Wextra -Werror
CC			=	gcc
LIB42		=	lib42
LIBFLAGS	+=	-lreadline
LIBFLAGS	+=	-Llib42 -lft
# LIBFLAGS	+=	-L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include
SANITIZE	=	-fsanitize=address -g3

FILES		=	main		\
				build_ins	\
				execve		\

SRCS		=	$(addsuffix .c, $(FILES))
OBJS		=	$(addsuffix .o, $(FILES))

all: $(OBJS)
	@make -C lib42
	@echo "$(B_GREEN)Compiling $(OBJS)$(C_ENDR)"
	@gcc $(CFLAGS) $(OBJS) $(LIBFLAGS) -o $(NAME) && ./$(NAME)

%.o: %.c
	@echo "$(B_GREEN)Creating object file: $<$(C_ENDR)"
	@$(CC) $(CFLAGS) -c $< -o $@

libftfclean:
	@make fclean -C lib42

clean:
	@echo "$(B_RED)Removing $(NAME) object files$(C_END)"
	@$(RM) $(OBJS)

fclean:	clean
	@echo "$(B_RED)Removing $(NAME)$(C_END)"
	@$(RM) $(NAME)

re:	fclean all