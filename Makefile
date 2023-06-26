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
C_GREEN	=	\033[1;32m
C_RED	=	\033[1;31m
C_BLUE	=	\033[1;34m
C_END 	=	\033[0m

NAME		=	minishell
CFLAGS		=	-Wall -Wextra -Werror
CC			=	gcc
LIBFT		=	libft
LIBFLAGS	+=	-lreadline
LIBFLAGS	+=	-Llibft -lft
# LIBFLAGS	+=	-L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include
SANITIZE	=	-fsanitize=address -g3

FILES		=	main		\
				utils		\
				build_ins	\
				executable	\
				lexer		\
				parser		\

SRCS		=	$(addsuffix .c, $(FILES))
OBJS		=	$(addsuffix .o, $(FILES))

all: $(NAME)

$(NAME): $(OBJS)
	@make -s -C libft
	@gcc $(CFLAGS) $(OBJS) $(LIBFLAGS) -o $(NAME)
	@echo "$(B_GREEN)Compiling $(OBJS)$(C_END)"
	@echo "$(C_GREEN)Makefile for minishell completed.$(C_END)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(B_GREEN)Creating object file: $<$(C_END)"


clean:
	@$(RM) $(OBJS)
	@echo "$(B_RED)Removing $(NAME) object files$(C_END)"

fclean:	clean
	@$(RM) $(NAME)
	@echo "$(C_RED)Removing $(NAME)$(C_END)"

lclean:
	@make fclean -s -C libft

re:	lclean fclean all