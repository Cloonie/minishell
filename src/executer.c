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

#include "../includes/minishell.h"

int	check_build_ins(t_list **lst)
{
	if (!(*lst)->args[0])
		return (1);
	if (!ft_strncmp((*lst)->args[0], "echo\0", 5))
		;
	else if (!ft_strncmp((*lst)->args[0], "pwd\0", 4))
		;
	else if (!ft_strncmp((*lst)->args[0], "export\0", 7))
		;
	else if (!ft_strncmp((*lst)->args[0], "unset\0", 6))
		;
	else if (!ft_strncmp((*lst)->args[0], "env\0", 4))
		;
	else if (!ft_strncmp((*lst)->args[0], "cd\0", 3))
		;
	else if (!ft_strncmp((*lst)->args[0], "exit\0", 5))
		;
	else if ((!ft_strncmp((*lst)->args[0], "./", 2)
			|| !ft_strncmp((*lst)->args[0], "/", 1)))
		;
	else
		return (1);
	return (0);
}

int	run_build_ins(t_minishell *ms, t_list **lst)
{
	if (!(*lst)->args[0])
		return (1);
	if (!ft_strncmp((*lst)->args[0], "echo\0", 5))
		call_echo(ms, (*lst));
	else if (!ft_strncmp((*lst)->args[0], "pwd\0", 4))
	{
		printf("%s\n", ms->cwd);
		ms->exit_status = 0;
	}
	else if (!ft_strncmp((*lst)->args[0], "export\0", 7))
		call_export(ms, (*lst));
	else if (!ft_strncmp((*lst)->args[0], "unset\0", 6))
		call_unset(ms, (*lst));
	else if ((!ft_strncmp((*lst)->args[0], "env\0", 4)))
		call_env(ms, (*lst));
	else if (!ft_strncmp((*lst)->args[0], "cd\0", 3))
		call_cd(ms, (*lst));
	else if (!ft_strncmp((*lst)->args[0], "exit\0", 5))
		myexit(ms, lst, 0);
	else if ((!ft_strncmp((*lst)->args[0], "./", 2)
			|| !ft_strncmp((*lst)->args[0], "/", 1)))
		call_run(ms, (*lst));
	else
		return (1);
	return (0);
}

int	cmd(t_minishell *ms, t_list **lst)
{
	if (((*lst))->args[0])
	{
		if (!check_build_ins(lst))
			return (1);
		else if (executable(ms, ((*lst))))
		{
			printf("minishell: %s: command not found\n", ((*lst))->args[0]);
			ms->exit_status = 127;
			return (1);
		}
	}
	return (0);
}

int	fork_pid(t_minishell *ms, t_list *lst, char **paths, int i)
{
	// pid_t	pid;
	char	buf[MAX_BUF];

	ft_strlcpy(buf, paths[i], MAX_BUF);
	ft_strlcat(buf, "/", MAX_BUF);
	ft_strlcat(buf, lst->args[0], MAX_BUF);
	if (access(buf, F_OK) == 0)
	{
		// pid = fork();
		// if (pid == 0)
		execve(buf, lst->args, ms->envp);
		printf("after execve\n");
		// else if (pid > 0)
		// {
			// waitpid(pid, &ms->exit_status, 0);
			// ms->exit_status = ms->exit_status >> 8;
			// i = -1;
			// while (paths[++i])
			// 	free(paths[i]);
			// free(paths);
			// return (1);
		// }
	}
	return (0);
}

int	executable(t_minishell *ms, t_list *lst)
{
	char	**paths;
	int		i;

	i = -1;
	paths = ft_split(ft_getenv(ms, "PATH"), ':');
	while (paths && paths[++i])
		if (fork_pid(ms, lst, paths, i))
			return (0);
	i = -1;
	while (paths && paths[++i])
		free(paths[i]);
	free(paths);
	return (1);
}
