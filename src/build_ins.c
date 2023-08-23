/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:23:16 by mliew             #+#    #+#             */
/*   Updated: 2023/04/09 15:23:16 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	call_echo2(t_minishell *ms, t_list *lst, int i, int newline)
{
	while (lst->args[i])
	{
		ft_putstr_fd(lst->args[i], 1);
		if (lst->args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", 1);
	ms->exit_status = 0;
}

void	call_echo(t_minishell *ms, t_list *lst)
{
	int	i;
	int	j;
	int	newline;

	i = 1;
	j = 1;
	newline = 1;
	while (lst->args[i])
	{
		if (lst->args[i][j - 1] != '-')
			break ;
		while (lst->args[i][j])
		{
			if (i == 1 && lst->args[i][j] == 'n' && !lst->args[i][j + 1])
				newline = 0;
			else if (lst->args[i][j] != 'n')
				break ;
			j++;
		}
		if (lst->args[i][j] && lst->args[i][j] != 'n')
			break ;
		j = 1;
		i++;
	}
	call_echo2(ms, lst, i, newline);
}

void	call_cd(t_minishell *ms, t_list *lst)
{
	char	path[100];

	if (lst->args[1])
	{
		ft_strlcpy(path, ms->cwd, 100);
		ft_strlcat(path, "/", 100);
		ft_strlcat(path, lst->args[1], 100);
		if (lst->args[1][0] == '/')
			chdir(lst->args[1]);
		else if (!access(path, F_OK))
			chdir(path);
		else
		{
			ft_printf("%s: %s: No such file or directory\n",
				lst->args[0], lst->args[1]);
			ms->exit_status = 1;
			return ;
		}
	}
	else
		chdir(ft_getenv(ms, "HOME"));
	ms->exit_status = 0;
}

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
