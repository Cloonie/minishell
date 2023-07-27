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

int	cmd_helper(t_minishell *ms, t_list *tmp)
{
	if (!ft_strncmp(tmp->args[0], "echo\0", 5))
		call_echo(ms, tmp);
	else if (!ft_strncmp(tmp->args[0], "pwd\0", 4))
	{
		printf("%s\n", ms->cwd);
		ms->exit_status = 0;
	}
	else if (!ft_strncmp(tmp->args[0], "export\0", 7))
		call_export(ms, tmp);
	else if (!ft_strncmp(tmp->args[0], "unset\0", 6))
		call_unset(ms, tmp);
	else if ((!ft_strncmp(tmp->args[0], "env\0", 4)))
		call_env(ms, tmp);
	else if (!ft_strncmp(tmp->args[0], "cd\0", 3))
		call_cd(ms, tmp);
	else
		return (1);
	return (0);
}

int	cmd(t_minishell *ms, t_list **lst, t_list *tmp)
{
	if (tmp->args[0])
	{
		if (!cmd_helper(ms, tmp))
			;
		else if (!ft_strncmp(tmp->args[0], "exit\0", 5))
			myexit(ms, lst, 0);
		else if ((!ft_strncmp(tmp->args[0], "./", 2)
				|| !ft_strncmp(tmp->args[0], "/", 1)))
			call_run(ms, tmp);
		else if (executable(ms, tmp))
		{
			printf("Enter a valid command.\n");
			ms->exit_status = 127;
			return (1);
		}
	}
	return (0);
}

int	executable(t_minishell *ms, t_list *lst)
{
	pid_t	pid;
	char	**paths;
	char	buf[100];
	int		i;

	i = -1;
	paths = ft_split(ft_getenv(ms, "PATH"), ':');
	while (paths && paths[++i])
	{
		ft_strlcpy(buf, paths[i], 100);
		ft_strlcat(buf, "/", 100);
		ft_strlcat(buf, lst->args[0], 100);
		if (access(buf, F_OK) == 0)
		{
			pid = fork();
			if (pid == 0)
				execve(buf, lst->args, ms->envp);
			else if (pid > 0)
			{
				waitpid(pid, &ms->exit_status, 0);
				ms->exit_status = ms->exit_status >> 8;
				i = -1;
				while (paths[++i])
					free(paths[i]);
				free(paths);
				return (0);
			}
		}
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (1);
}
