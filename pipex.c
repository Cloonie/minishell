#include "minishell.h"

int     executable(char **input, char **envp);

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
		if (pipe_vars->here_doc_flag == 1)
		{
			*fdout = open(pipe_vars->argv[pipe_vars->argc - 1],
					O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (*fdout == -1)
			{
				perror("Outfile");
				exit(1);
			}
		}
		else
		{
			*fdout = open(pipe_vars->argv[pipe_vars->argc - 1],
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (*fdout == -1)
			{
				perror("Outfile");
				exit(1);
			}
		}
	}
}

void	redir(int i, int *fdin, int *fdout, t_pipe *pipe_vars)
{
	int	fdpipe[2];

	if (dup2(*fdin, 0) == -1)
	{
		perror("dup2");
		exit(1);
	}
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

void	run_child(t_pipe *pipe_vars, int i)
{
	if (pipe_vars->here_doc_flag == 1)
	{
		if (i == 0)
			executable(&pipe_vars->argv[i + 3], pipe_vars->envp);
		else
			executable(&pipe_vars->argv[i + 3], pipe_vars->envp);
	}
	else
		executable(&pipe_vars->argv[i + 2], pipe_vars->envp);
}

void	fork_process(t_pipe *pipe_vars, int *fdin, int *fdout)
{
	int	child;
	int	i;

	i = 0;

	while (i < pipe_vars->numcmd)
	{
		redir(i, fdin, fdout, pipe_vars);
		child = fork();
		if (child == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (child == 0)
		{
			run_child(pipe_vars, i);
			exit(0);
		}
		i++;
	}
}