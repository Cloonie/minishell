/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:44:31 by mliew             #+#    #+#             */
/*   Updated: 2023/07/11 22:44:31 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipex(t_minishell *ms, t_list **lst)
{
	int	size;
	int	fdpipe[2];
	int	i;
	int	piped;

	size = ft_lstsize(*lst);
	ms->ori_in = dup(0);
	ms->ori_out = dup(1);
	ms->fdin = 0;
	ms->fdout = 0;
	piped = 0;

	i = -1;
	while (++i < size)
	{
		if ((*lst)->infile)
		{
			ms->fdin = open((*lst)->infile, O_RDONLY);
			if (ms->fdin == -1)
			{
				(*lst)->infile = NULL;
				perror("Error opening file");
				return ;
			}
		}
		else if (piped)
			piped = 0;
		else
			ms->fdin = dup(ms->ori_in);
		dup2(ms->fdin, 0);
		close(ms->fdin);

		if ((*lst)->outfile && !(*lst)->append)
			ms->fdout = open((*lst)->outfile,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if ((*lst)->outfile && (*lst)->append)
			ms->fdout = open((*lst)->outfile,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if ((*lst)->next)
		{
			pipe(fdpipe);
			ms->fdout = fdpipe[1];
			ms->fdin = fdpipe[0];
		}
		else
			ms->fdout = dup(ms->ori_out);
		dup2(ms->fdout, 1);
		close(ms->fdout);

		cmd(ms, lst);

		if ((*lst)->next)
		{
			pipe(fdpipe);
			ms->fdout = fdpipe[1];
			dup2(ms->fdout, 1);
			close(ms->fdout);
			ms->fdin = fdpipe[0];
			piped = 1;
		}
		(*lst) = (*lst)->next;
	}

	dup2(ms->ori_in, 0);
	dup2(ms->ori_out, 1);
	close(ms->ori_in);
	close(ms->ori_out);
}
