# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/17 14:01:46 by mliew             #+#    #+#              #
#    Updated: 2023/04/21 10:56:13 by mliew            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

B_GREEN=	\033[38;5;121m
B_RED	=	\033[38;5;204m
C_GREEN	=	\033[0;32m
C_RED	=	\033[0;31m
C_BLUE	=	\033[0;34m
C_END 	=	\033[0m
C_ENDR	=	\033[0m\r

NAME		=	libft.a
OBJS		=	$(SRCS:.c=.o)
CFLAGS		=	-Wall -Wextra -Werror -I ./
CC			=	gcc
RM			=	rm -rf
AR			=	ar rcs

INCLUDES	= ./includes
SRC_PATH	= ./src
OBJ_PATH	= ./obj

SRCS	= $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*/*,.c*)))
OBJS	= $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRCS)))))

# $(foreach)	- replaces var1 with var2 and creates a different path for each var1.
# $(notdir)		- takes away the directory path from the file name	e.g lib42/src/main.c
# $(basename)	- takes away the extension type of the file name	e.g main.c -> main

all: $(NAME)

$(NAME):			$(OBJ_PATH)	$(OBJS)
					@$(AR) $(NAME) $(OBJS)
					@echo "$(B_GREEN)Archiving $@...$(C_ENDR)"
					@echo "$(B_GREEN)Makefile completed.$(C_ENDR)"

$(OBJ_PATH)/%.o:	$(SRC_PATH)/*/%.c*
					@echo "$(B_GREEN)Compiling $<...$(C_ENDR)"
					@$(CC) $(CFLAGS) -c -I$(INCLUDES) $< -o $@

$(OBJ_PATH):
					@echo "$(B_GREEN)Creating object path...$(C_END)"
					@mkdir -p $(OBJ_PATH)

clean:
					@echo "$(B_RED)Removing object files...$(C_END)"
					@$(RM) $(OBJ_PATH)

fclean:				clean
					@echo "$(B_RED)Removing $(NAME)...$(C_END)"
					@$(RM) $(NAME)

re:					fclean all