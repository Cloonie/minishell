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
READLINE	=	-lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include
LIBFLAGS	=	-Llibft -lft
# SANITIZE	=	-fsanitize=address -g3

INCLUDES	=	./includes
SRC_PATH	=	./src
OBJ_PATH	=	./obj

SRCS	=	$(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*, .c*)))
OBJS	=	$(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRCS)))))

all: $(NAME)

$(NAME): $(SRCS)
	@make -s -C libft
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME) $(LIBFLAGS) $(READLINE)
	@echo "$(B_GREEN)Compiling $(C_END)"
	@echo "$(C_GREEN)Makefile for minishell completed.$(C_END)"

# $(OBJ_PATH)/%.o:	$(SRC_PATH)/%.c*
# 					@mkdir -p $(OBJ_PATH)
# 					@echo "$(B_GREEN)Creating object file: $<$(C_ENDR)"
# 					@$(CC) $(CFLAGS) -c $< -o $@ $(READLINE)
# @rm -rf $(OBJ_PATH)

clean:
	@echo "$(B_RED)Removing $(NAME) object files$(C_END)"

fclean:	clean
	@$(RM) $(NAME) 
	@echo "$(C_RED)Removing $(NAME)$(C_END)"

lclean:
	@make fclean -s -C libft

re:	lclean fclean all