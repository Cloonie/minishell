CFLAGS = -Wall -Wextra -Werror
CFLAGS += -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include

LIB42	=	lib42
LDFLAGS	=	-Llib42 -lft
SANITIZE=	-fsanitize=address -g3

all:
	make -C lib42
	gcc $(CFLAGS) $(LDFLAGS) main.c && ./a.out