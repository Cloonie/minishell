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

void	handle_pipe(t_minishell *ms)
{
	t_pipe	p_vars;
	int		i;

	i = 0;
	p_vars.numcmd = 0;
	while (ms->input[i])
	{
		if (ms->token[i] == TOK_CMD)
			p_vars.numcmd++;
		i++;
	}

	fork_process(&p_vars, ms);
	parent_wait(&p_vars);
}

int		fork_process(t_pipe *p_vars, t_minishell *ms)
{
	int	child;
	int	i;

	i = 0;
	while (i < p_vars->numcmd)
	{
		child = fork();
		if (child == -1)
		{
			perror("fork");
			return (1);
		}
		else if (child == 0)
		{
			if (ms->token[i] == TOK_CMD)
				cmd(ms, i);
		}
		i++;
	}
	return (0);
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