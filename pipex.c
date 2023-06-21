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
		if (pipe_vars->here_doc_flag == 1)
		{
			*fdout = open(pipe_vars->argv[pipe_vars->argc - 1], O_WRONLY | O_APPEND, 0644);
			if (*fdout == -1)
			{
				perror("Outfile");
				exit(1);
			}
		}
		else
		{
			*fdout = open(pipe_vars->argv[pipe_vars->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (*fdout == -1)
			{
				perror("Outfile");
				exit(1);
			}
		}
	}
}

void	output_redir(int i, int *fdin, int *fdout, t_pipe *pipe_vars)
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

void	fork_process(t_pipe *pipe_vars, int *fdin, int *fdout)
{
	int	child;
	int	i;

	i = 0;

	while (i < pipe_vars->numcmd)
	{
		output_redir(i, fdin, fdout, pipe_vars);
		child = fork();
		if (child == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (child == 0)
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
			exit(0);
		}
		i++;
	}
}

void	first_input_redir(char **argv, int *fdin, t_pipe *pipe_vars)
{
	char	*input;
	
	(void)pipe_vars;

	if (ft_strncmp(pipe_vars->argv[1], "here_doc", 9) == 0)
	{
		pipe_vars->here_doc_flag = 1;
		pipe_vars->numcmd -= 1;
		pipe_vars->tmp = open("here_doc", O_WRONLY | O_CREAT, 0644);
		if (pipe_vars->tmp == -1)
		{
			perror("here_doc");
			exit(1);
		}
		while ((input = readline("> ")) != NULL)
		{
			if ((ft_strncmp(input, pipe_vars->argv[2], ft_strlen(pipe_vars->argv[2]) + 1) == 0))
			{
				free(input);
				break ;
			}
			write(pipe_vars->tmp, input, ft_strlen(input));
			write(pipe_vars->tmp, "\n", 1);
			free(input);
		}
		close(pipe_vars->tmp);
		*fdin = open("here_doc", O_RDONLY);
		unlink("here_doc");
	}
	else
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
	pipe_vars.here_doc_flag = 0;

	first_input_redir(argv, &fdin, &pipe_vars);
	fork_process(&pipe_vars, &fdin, &fdout);
	
	dup2(pipe_vars.tmpin, 0);
	dup2(pipe_vars.tmpout, 1);
	close(pipe_vars.tmpin);
	close(pipe_vars.tmpout);

	parent_wait(&pipe_vars);

	return(0);
}
