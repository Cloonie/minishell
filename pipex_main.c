/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheong <kcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:42:04 by kcheong           #+#    #+#             */
/*   Updated: 2023/06/22 13:10:20 by kcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(t_pipe *pipe_vars, int *fdin, char *input)
{
	pipe_vars->here_doc_flag = 1;
	pipe_vars->numcmd -= 1;
	pipe_vars->tmp = open("here_doc", O_WRONLY | O_CREAT, 0644);
	if (pipe_vars->tmp == -1)
	{
		perror("here_doc");
		exit(1);
	}
	input = readline("> ");
	while (input != NULL)
	{
		if ((ft_strncmp(input, pipe_vars->argv[2],
					ft_strlen(pipe_vars->argv[2]) + 1) == 0))
		{
			free(input);
			break ;
		}
		write(pipe_vars->tmp, input, ft_strlen(input));
		write(pipe_vars->tmp, "\n", 1);
		free(input);
		input = readline("> ");
	}
	close(pipe_vars->tmp);
	*fdin = open("here_doc", O_RDONLY);
	unlink("here_doc");
}

void	first_input_redir(int *fdin, t_pipe *pipe_vars)
{
	char	*input;

	input = NULL;
	if (ft_strncmp(pipe_vars->argv[1], "here_doc", 9) == 0)
		here_doc(pipe_vars, fdin, input);
	else
	{
		if (pipe_vars->argv[1])
		{
			*fdin = open(pipe_vars->argv[1], O_RDONLY);
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

	first_input_redir(&fdin, &pipe_vars);
	fork_process(&pipe_vars, &fdin, &fdout);

	dup2(pipe_vars.tmpin, 0);
	dup2(pipe_vars.tmpout, 1);
	close(pipe_vars.tmpin);
	close(pipe_vars.tmpout);

	parent_wait(&pipe_vars);
	return (0);
}
