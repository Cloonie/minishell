CFLAGS = -Wall -Wextra -Werror
CFLAGS += -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include

all:
	gcc $(CFLAGS) main.c && ./a.out