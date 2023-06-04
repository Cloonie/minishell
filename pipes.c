#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>

int	main()
{
	int		pipe_fd[2];
	int		cpid;
	char	buffer[100];
	int		store_to;

	pipe(pipe_fd);

	cpid = fork();
	store_to = open("test.txt", O_WRONLY | O_APPEND);
	if (cpid == 0) 
	{
		write(pipe_fd[1], "Hello from child", 18);
		close(pipe_fd[0]);
		exit(0);
	}
	else if (cpid > 0)
	{
		wait(NULL);
		read(pipe_fd[0], &buffer, 100);
		dup2(store_to, STDOUT_FILENO);
		printf("Received message [%s].\n", buffer);
		close(pipe_fd[1]);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);

	wait(NULL);
	printf("DONE :D\n");
}