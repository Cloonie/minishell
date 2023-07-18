/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:51:54 by mliew             #+#    #+#             */
/*   Updated: 2023/05/07 15:51:54 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd(t_minishell *ms, t_list **lst, int pid)
{
	t_list	*tmp;

	tmp = *lst;
	// printf("tmp->args[0]: %s\n", tmp->args[0]);
	if (tmp->args[0])
	{
		if (!ft_strncmp(tmp->args[0], "echo\0", 5) && pid > 0)
			call_echo(tmp);
		else if (!ft_strncmp(tmp->args[0], "pwd\0", 4 && pid > 0))
			printf("%s\n", ms->cwd);
		else if (!ft_strncmp(tmp->args[0], "export\0", 7 && pid > 0))
			call_export(ms, tmp);
		else if (!ft_strncmp(tmp->args[0], "unset\0", 6 && pid > 0))
			call_unset(tmp->args, ms->envp);
		else if ((!ft_strncmp(tmp->args[0], "env\0", 4 && pid > 0)))
			call_env(ms);
		else if (!ft_strncmp(tmp->args[0], "cd\0", 3 && pid > 0))
			call_cd(ms, tmp);
		else if (!ft_strncmp(tmp->args[0], "exit\0", 5 && pid > 0))
			myexit(0);
		else if ((!ft_strncmp(tmp->args[0], "./", 2) == 0
			|| !ft_strncmp(tmp->args[0], "/", 1) == 0) && pid > 0)
			call_run(tmp->args, ms->envp);
		else if (executable(ms, tmp, pid))
		{
			printf("Enter a valid command.\n");
			return (1);
		}
		else
			return (1);
	}
	return (0);
}

int	executable(t_minishell *ms, t_list *lst, int pid)
{
	char	**paths;
	char	*current_path;
	int		i;

	i = -1;
	paths = ft_split(ft_getenv(ms, "PATH"), ':');
	while (paths && paths[++i])
	{
		current_path = ft_strjoin(ft_strjoin(paths[i], "/"), lst->args[0]);
		if (access(current_path, F_OK) == 0)
		{
			(void)pid;
			// pid_t	pid;
			// pid = fork();
			// if (pid == 0)
				execve(current_path, lst->args, ms->envp);
			// else if (pid > 0)
			// {
				waitpid(pid, &ms->exit_status, 0);
				ms->exit_status = ms->exit_status >> 8;
			// }
		}
	}
	return (1);
}
