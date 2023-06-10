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

void	executable(char **input, char **envp);

void	runcmd(char **cmd, char **envp, int file1, int file2)
{
	if (dup2(file1, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}
	if (dup2(file2, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(file1);
	close(file2);
	executable(cmd, envp);
	
	perror(cmd[0]);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	child1;
	pid_t	child2;
	
	if (argc != 5)
	{
		printf("Usage: ./pipex infile cmd1 cmd2 outfile\n");
		exit(1);
	}

	pipe(pipe_fd);

	child1 = fork();
	if (child1 == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		char *cmd[] = {argv[2], NULL};
		int infile = open(argv[1], O_RDONLY);
		close(pipe_fd[0]);
		runcmd(cmd, envp, infile, pipe_fd[1]);
	}

	child2 = fork();
	if (child2 == 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		char *cmd[] = {argv[3], NULL};
		int	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		close(pipe_fd[1]);
		runcmd(cmd, envp, pipe_fd[0], outfile);
	}
	
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(child1, 0, 0);
	waitpid(child2, 0, 0);
}