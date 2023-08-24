/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew < mliew@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:11:11 by mliew             #+#    #+#             */
/*   Updated: 2023/08/24 18:26:47 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_run(t_minishell *ms, t_list **lst)
{
	input(ms, lst);
	output(ms, lst);
	signal_handler(1);
	run_build_ins(ms, lst);
	cmd(ms, lst);
	exit(ms->exit_status);
}

void	child_loop(t_minishell *ms, t_list **lst, int i, pid_t *child)
{
	while ((*lst))
	{
		if ((*lst)->next)
			pipe((*lst)->next->fdpipe);
		if ((*lst)->delimiter)
			here_doc(ms, lst);
		child[++i] = fork();
		if (child[i] == 0)
			child_run(ms, lst);
		else
		{
			close((*lst)->fdpipe[0]);
			if ((*lst)->next)
				close((*lst)->next->fdpipe[1]);
			(*lst) = (*lst)->next;
		}
	}
	i = -1;
	while (child[++i])
	{
		waitpid(child[i], &ms->exit_status, 0);
		ms->exit_status = ms->exit_status % 255;
	}
}

void	final(t_minishell *ms, t_list **lst)
{
	t_list	*head;
	pid_t	*child;
	int		i;

	i = -1;
	head = *lst;
	child = malloc(sizeof(pid_t) * ft_lstsize(*lst));
	init_pipe(ms);
	signal_handler(1);
	if (!check_build_ins(lst) && !(*lst)->next)
		run_build_ins(ms, lst);
	else
	{
		child_loop(ms, lst, i, child);
		dup2(ms->ori_in, 0);
		dup2(ms->ori_out, 1);
		close(ms->ori_in);
		close(ms->ori_out);
	}
	unlink(".tmp");
	free(child);
	*lst = head;
}
