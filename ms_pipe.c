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

void	lastcmd(t_minishell *ms)
{
	printf("yaaa\n");
	if (ms->outfile)
	{
		ms->fdout = open(ms->outfile,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (ms->fdout == -1)
			perror("Outfile");
	}
	else
		ms->fdout = dup(ms->tmpout);
}

int	parent_wait(t_list **lst)
{
	int	i;

	i = 0;
	while (i < ft_lstsize(*lst))
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

void	redir(t_minishell *ms, t_list **lst, int i)
{
	int	fdpipe[2];

	if (dup2(ms->fdin, 0) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(ms->fdin);
	if (i == (ft_lstsize(*lst) - 1))
		lastcmd(ms);
	else
	{
		pipe(fdpipe);
		ms->fdout = fdpipe[1];
		ms->fdin = fdpipe[0];
	}
	dup2(ms->fdout, 1);
	close(ms->fdout);
}

int	fork_process(t_minishell *ms, t_list **lst)
{
	int	child;
	int	i;

	(void)ms;
	i = 0;
	while (i < ft_lstsize(*lst))
	{
		redir(ms, lst, i);
		child = fork();
		if (child == -1)
		{
			perror("fork");
			return (1);
		}
		else if (child == 0)
		{
			cmd(ms, lst);
			exit(1);
		}
		i++;
	}
	return (0);
}

int	handle_pipe(t_minishell *ms, t_list **lst)
{
	ms->tmpin = dup(STDIN_FILENO);
	ms->tmpout = dup(STDOUT_FILENO);
	if (ms->infile)
	{
		ms->fdin = open(ms->infile, O_RDONLY);
		if (ms->fdin == -1)
			perror("infile");
	}
	else
	{
		ms->fdin = dup(ms->tmpin);
		if (ms->fdin == -1)
			perror("dup");
	}
	fork_process(ms, lst);
	dup2(ms->tmpin, 0);
	dup2(ms->tmpout, 1);
	close(ms->tmpin);
	close(ms->tmpout);
	// parent_wait(lst);
	return (0);
}
