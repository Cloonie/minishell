#include "minishell.h"

void	executable(char **input, char **envp);

void	parent_wait(t_pipe *pipe_vars)
{
	int	i;

	i = 0;
	while (i < pipe_vars->numcmd)
	{
		if (wait(NULL) == -1)
		{
			perror("Wait");
			exit(1);
		}
		i++;
	}
}

void	lastcmd(int *fdout, t_pipe *pipe_vars)
{
	if (pipe_vars->argv[pipe_vars->argc - 1])
	{
		*fdout = open(pipe_vars->argv[pipe_vars->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*fdout == -1)
		{
			perror("Outfile");
			exit(1);
		}
	}
	else
	{
		*fdout = dup(pipe_vars->tmpout);
		{
			perror("Outfile");
			exit(1);
		}
	}
}

void	output_redir(int i, int *fdin, int *fdout, t_pipe *pipe_vars)
{
	int fdpipe[2];

	dup2(*fdin, 0);
	close(*fdin);
	if (i == (pipe_vars->numcmd - 1))
		lastcmd(fdout, pipe_vars);
	else
	{
		pipe(fdpipe);
		*fdout = fdpipe[1];
		*fdin = fdpipe[0];
	}

	dup2(*fdout, 1);
	close(*fdout);
}

void	fork_process(t_pipe *pipe_vars, int *fdin, int *fdout)
{
	int	child;
	int	i;

	i = 0;
	while (i < pipe_vars->numcmd)
	{
		output_redir(i, fdin, fdout, pipe_vars);
		child = fork();
		if (child == 0)
			executable(&pipe_vars->argv[i + 2], pipe_vars->envp);
		i++;
	}
}

void	input_redir(char **argv, int *fdin, t_pipe *pipe_vars)
{
	if (argv[1])
	{
		*fdin = open(argv[1], O_RDONLY);
		if (*fdin == -1)
		{
			perror("Infile");
			exit(1);
		}
	}
	else
	{
		*fdin = dup(pipe_vars->tmpin);
		if (*fdin == -1)
		{
			perror("Infile");
			exit(1);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		fdin;
	int		fdout;
	t_pipe	pipe_vars;

	pipe_vars.numcmd = argc - 3;
	pipe_vars.tmpin = dup(0);
	pipe_vars.tmpout = dup(1);
	pipe_vars.argv = argv;
	pipe_vars.argc = argc;
	pipe_vars.envp = envp;

	input_redir(argv, &fdin, &pipe_vars);
	fork_process(&pipe_vars, &fdin, &fdout);
	
	dup2(pipe_vars.tmpin, 0);
	dup2(pipe_vars.tmpout, 1);
	close(pipe_vars.tmpin);
	close(pipe_vars.tmpout);

	parent_wait(&pipe_vars);

	return(0);
}