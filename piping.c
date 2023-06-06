#include "minishell.h"

// argv[1] = input file
// argv[4] = output file
// argv[2] = command 1
// argv[3] = command 2
// 1. Establish a pipe so forked child processes can communicate between each other.
// 2. Child1 runs command 1, child2 runs command 2.
// 3. Output of child1 should go to the write end of the pipe (instead of STDOUT, i.e. terminal), 
//    so that the output can be read by child2 through the read end of the pipe.
//    [dup2(pipe[1], STDOUT_FILENO)]
// 	  After setting up the correct output stream, it can then execute its command.
// 4. Input of child2 should come from the read end of the pipe (which is connected to the output of child1),
//    [dup2(pipe[0], STDIN_FILENO)]
//    After setting up the correct input stream, it can then execute its command.
// 5. When child1 is executing its command, input file should replace the standard input.
//    [dup2(argv[1], STDIN_FILENO)]
// 6. When child2 is executing its command, output file should replace the standard output.
// 7. Remember to close unused fd in both child and parent process. And wait if necessary. 

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;
	int		x = 0;
	int		pipe_fd[2];
	pid_t	child1;
	pid_t	child2;

	// if (argc != 5)
	// {
	// 	printf("Usage: ./pipex infile cmd1 cmd2 outfile\n");
	// 	exit(1);
	// }

	// Establish a pipe so forked child processes can communicate between each other.
	pipe(pipe_fd);

	// Child1 runs command 1.
	child1 = fork();
	if (child1 == 0)
	{
		// Output of child1 should go to the write end of the pipe (instead of STDOUT, i.e. terminal), 
		// so that the output can be read by child2 through the read end of the pipe.
		dup2(pipe_fd[1], STDOUT_FILENO);

		// printf("Hi from child1");

		x += 5;
		// printf("%d\n", x);
		write(STDOUT_FILENO, &x, sizeof(int));
		
		close(pipe_fd[0]);
		// Do I need this? ⬇️
		// close(STDIN_FILENO);
		exit(0);
	}
	// Child2 runs command 2.
	child2 = fork();
	if (child2 == 0)
	{
		// Input of child2 should come from the read end of the pipe (which is connected to the output of child1).
		dup2(pipe_fd[0], STDIN_FILENO);

		// Redirect the output to output file instead of to the terminal.
		// int output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		// if (dup2(output, STDOUT_FILENO) == -1)
		// {
		// 	perror("Output dup2");
		// 	exit(1);
		// }

		// char buffer[20];
		// read(STDIN_FILENO, &buffer, 20);
		// printf("Message received: [%s]\n", buffer);

		read(STDIN_FILENO, &x, sizeof(int));
		printf("%d\n", x += 5);
		close(pipe_fd[1]);
		exit(0);
	}
	
	waitpid(child1, 0, 0);
	waitpid(child2, 0, 0);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}