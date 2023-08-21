/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:59:46 by mliew             #+#    #+#             */
/*   Updated: 2023/07/04 16:59:46 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	call_env(t_minishell *ms, t_list *lst)
{
	int	i;

	i = 0;
	if (lst->args[1])
	{
		perror(lst->args[1]);
		ms->exit_status = 127;
		return ;
	}
	while (ms->envp[i])
	{
		if (ft_strchr(ms->envp[i], '='))
			ft_printf("%s\n", ms->envp[i++]);
		else
			i++;
	}
	ms->exit_status = 0;
}

void	call_run(t_minishell *ms, t_list *lst)
{
	int		pid;

	if (access(lst->args[0], F_OK) == 0)
	{
		pid = fork();
		if (pid == 0)
			execve(lst->args[0], lst->args, ms->envp);
		else if (pid > 0)
		{
			waitpid(pid, &ms->exit_status, 0);
			ms->exit_status = ms->exit_status >> 8;
			return ;
		}
	}
	else
	{
		perror(lst->args[0]);
		ms->exit_status = 127;
		return ;
	}
	ms->exit_status = 0;
}
