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
NAME2		= 	pipex
CFLAGS		=	-Wall -Wextra -Werror
CC			=	gcc
LIBFT		=	libft
LIBFLAGS	+=	-lreadline
LIBFLAGS	+=	-Llibft -lft
SANITIZE	=	-fsanitize=address -g3

FILES		=	main		\
				utils		\
				lexer		\
				token		\
				parser		\
				build_ins	\
				build_ins2	\
				executer	\
				ms_pipe		\
				# spipe_sample\

SRCS		=	$(addsuffix .c, $(FILES))
OBJS		=	$(addsuffix .o, $(FILES))
# SRCS2		=	$(addsuffix .c, $(PIPEX_FILES))
# OBJS2		=	$(addsuffix .o, $(PIPEX_FILES))

all: $(NAME)
# all: $(NAME) $(NAME2)

$(NAME): $(OBJS)
	@make -s -C libft
	@gcc $(CFLAGS) $(OBJS) $(LIBFLAGS) -o $(NAME)
	@echo "$(B_GREEN)Compiling $(OBJS)$(C_END)"
	@echo "$(C_GREEN)Makefile for minishell completed.$(C_END)"

# $(NAME2): $(OBJS2)
# 	@make -s -C libft
# 	@gcc $(CFLAGS) $(OBJS2) $(LIBFLAGS) -o $(NAME2)
# 	@echo "$(B_GREEN)Compiling $(OBJS2)$(C_END)"
# 	@echo "$(C_GREEN)Makefile for pipex completed.$(C_END)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(B_GREEN)Creating object file: $<$(C_END)"

clean:
	@$(RM) $(OBJS) $(OBJS2)
	@echo "$(B_RED)Removing $(NAME) object files$(C_END)"

fclean:	clean
	@$(RM) $(NAME) $(NAME2) $(NAME3)
	@echo "$(C_RED)Removing $(NAME)$(C_END)"

lclean:
	@make fclean -s -C $(LIBFT)

re:	lclean fclean all