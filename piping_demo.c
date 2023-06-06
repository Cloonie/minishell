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
	// int		store_to;

	pipe(pipe_fd);

	cpid = fork();
	// store_to = open("test.txt", O_WRONLY | O_APPEND);
	if (cpid == 0) 
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		printf("This message goes to the write end of the pipe");
		// write(pipe_fd[1], "Hello from child no.1", 22); 
		// Instead of using "write" to write the message to the write end of the pipe, use "dup2" to redirect the printf output to the pipe.
		close(pipe_fd[0]);
		exit(0);
	}
	cpid = fork();
	if (cpid == 0)
	{
		// dup2(store_to, STDOUT_FILENO);
		// Instead of printing output to the terminal, we can use "dup2" to redirect the output to a file we wanted to store the message.
		// Redirecting the STDIN_FILENO to the read end of the file, now our input is from the pipe. When we use "read" function, the "0" is not
		// the standard input (terminal) anymore.
		dup2(pipe_fd[0], STDIN_FILENO);
		read(0, &buffer, 100);
		printf("Child no.2 received message [%s].\n", buffer);
		close(pipe_fd[1]);
		exit(0);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);

	wait(NULL);
	printf("Parent says DONE :D\n");
}
