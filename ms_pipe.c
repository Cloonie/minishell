/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheong <kcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 10:24:40 by kcheong           #+#    #+#             */
/*   Updated: 2023/06/27 10:24:40 by kcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lastcmd( t_minishell *ms, int *fdout, t_pipe *p_vars)
{
	if (ms->outfile)
	{
		*fdout = open(ms->outfile,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*fdout == -1)
		{
			perror("Outfile");
		}
	}
	else
		*fdout = dup(p_vars->tmpout);
}

int		parent_wait(t_pipe *p_vars)
{
	int	i;

	i = 0;
	while (i < p_vars->numcmd)
	{
		if (wait(NULL) == -1)
		{
			perror("wait");
			return (1);
		}
		i++;
	}
	return (0);
}

void	redir(t_minishell *ms, t_pipe *p_vars, int i, int *fdin, int *fdout)
{
	int	fdpipe[2];

	(void)p_vars;
	if (dup2(*fdin, 0) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(*fdin);
	if (i == (p_vars->numcmd - 1))
		lastcmd(ms, fdout, p_vars);
	else
	{
		pipe(fdpipe);
		*fdout = fdpipe[1];
		*fdin = fdpipe[0];
	}
	dup2(*fdout, 1);
	close(*fdout);
}

int		fork_process(t_pipe *p_vars, t_minishell *ms, int *fdin, int *fdout)
{
	int	child;
	int	i;

	i = 0;
	while (i < p_vars->numcmd)
	{
		redir(ms, p_vars, i, fdin, fdout);
		child = fork();
		if (child == -1)
		{
			perror("fork");
			return (1);
		}
		else if (child == 0)
		{
			// how to run the command????
			printf("yes\n");
			if (ms->token[i] == TOK_CMD) 
			{
                execvp(ms->input[i], ms->input);
                perror("execvp");
                exit(1);
			}
		}
		i++;
	}
	return (0);
}

void	handle_pipe(t_minishell *ms)
{
	t_pipe	p_vars;
	int		i;
	int		fdin;
	int		fdout;

	i = 0;
	p_vars.tmpin = dup(STDIN_FILENO);
	p_vars.tmpout = dup(STDOUT_FILENO);
	p_vars.numcmd = 0;
	(void)fdout;
	while (ms->input[i])
	{
		if (ms->token[i] == TOK_CMD)
			p_vars.numcmd++;
		i++;
	}

	if (ms->infile)
	{
		fdin = open(ms->infile, O_RDONLY);
		if (fdin == -1)
			perror("infile");
	}
	else
	{
		fdin = dup(p_vars.tmpin);
		if (fdin == -1)
			perror("dup");
	}
	fork_process(&p_vars, ms, &fdin, &fdout);
	parent_wait(&p_vars);
}
