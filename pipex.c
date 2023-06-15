#include "minishell.h"

void	executable(char **input, char **envp);

int	main(int argc, char **argv, char **envp)
{
	int	numcmd;
	int	tmpin;
	int	tmpout;
	int	fdin;
	int	fdout;

	numcmd = argc - 3;
	tmpin = dup(0);
	tmpout = dup(1);

	if (argv[1])
	{
		fdin = open(argv[1], O_RDONLY);
		if (fdin == -1)
		{
			perror("Infile");
			exit(1);
		}
	}
	else
	{
		fdin = dup(tmpin);
		if (fdin == -1)
		{
			perror("Infile");
			exit(1);
		}
	}
	
	int	child;
	int	i;

	i = 0;
	while (i < numcmd)
	{
		dup2(fdin, 0);
		close(fdin);
		if (i == numcmd - 1)
		{
			if (argv[argc - 1])
			{
				fdout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fdout == -1)
				{
					perror("Outfile");
					exit(1);
				}
			}
			else
			{
				fdout = dup(tmpout);
				{
					perror("Outfile");
					exit(1);
				}
			}
		}
		else
		{
			int fdpipe[2];
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}

		dup2(fdout, 1);
		close(fdout);

		child = fork();
		if (child == 0)
			executable(&argv[i + 2], envp);
		i++;
	}

	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);

	i = 0;
	while (i < numcmd)
	{
		if (wait(NULL) == -1)
		{
			perror("Wait");
			exit(1);
		}
		i++;
	}

	return(0);
}