# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mliew < mliew@student.42kl.edu.my>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/17 14:01:46 by mliew             #+#    #+#              #
#    Updated: 2022/09/17 19:35:53 by mliew            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
					$(AR) $(NAME) $(OBJS)

$(OBJ_PATH)/%.o:	$(SRC_PATH)/*/%.c*
					$(CC) $(CFLAGS) -c -I$(INCLUDES) $< -o $@

$(OBJ_PATH):
					mkdir -p $(OBJ_PATH)

clean:
					$(RM) $(OBJ_PATH)

fclean:				clean
					$(RM) $(NAME)

re:					fclean all