#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include "minishell.h"

// ./pipex file1 cmd1 cmd2 file2
// establish a pipe so cmd1 and cmd2 can communicate
// argv[1]: file1, standard input for cmd1 should be redirected to file1 - how?
// 				   standard output of cmd1 should be redirected to the write end of pipe so that cmd2 can read from it?
// argv[4]: file2, the write end of pipe should be redirected to file2, so the output is written in file2, not terminal.
// fork twice bcuz there is two commands, each child runs a command.
// remember to close unused fd
// parent has to wait until all the forked children finish their process?
// does children 2 has to wait for children 1?

void	executable(char **input, char **envp);

void	execute_cmd(int infile, int outfile, char **cmd, char **envp)
{
    (void)infile;
	// if (dup2(infile, STDIN_FILENO) == -1)
    // {
	// 	perror("3 Dup2");
	// 	exit(1);
	// }
	if (dup2(outfile, STDOUT_FILENO) == -1)
	{
		perror("4 Dup2");
		exit(1);
	}
	executable(cmd, envp);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		printf("Usage: ./pipex file1 cmd1 cmd2 file2");
		exit(1);
	}
	
	int	infile;
	int	outfile;
	int	pipefd[2];

	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
	{
		perror("Infile");
		exit(1);
	}
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		perror("Outfile");
		exit(1);
	}
	if (pipe(pipefd) == -1)
	{
		perror("Pipe");
		exit(1);
	}
	pid_t pid1;

	pid1 = fork();
	if (pid1 == 0)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			perror("1 Dup2");
			exit(1);
		}
		char *cmd1[] = {argv[2], NULL};
		executable(cmd1, envp);
		exit(0);
	}
	
	pid_t	pid2;

	pid2 = fork();
	if (pid2 == 0)
	{
		waitpid(pid1, 0, 0);
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
		{
			perror("2 Dup2");
			exit(1);
		} 

		// char *cmd2[] = {argv[3], NULL};
		// execute_cmd(infile, outfile, cmd2, envp);
		// close(pipefd[0]);
		// close(STDIN_FILENO);
		exit(0);
	}

	waitpid(pid1, 0, 0);
	waitpid(pid2, 0, 0);
	close(pipefd[0]);
	close(pipefd[1]);
	close(infile);
	close(outfile);
	exit(0);
}
