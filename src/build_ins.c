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

void	call_unset(t_minishell *ms, t_list *lst)
{
	char	*var;
	int		i;
	int		j;

	if (!lst->args[1])
		return ;
	j = 0;
	while (lst->args[++j])
	{
		i = -1;
		while (ms->envp[++i])
		{
			if (ft_strpos(ms->envp[i], "="))
				var = ft_substr(ms->envp[i], 0, ft_strpos(ms->envp[i], "="));
			else
				var = ft_substr(ms->envp[i], 0, ft_strlen(ms->envp[i]));
			if (!ft_strncmp(lst->args[j], var, ft_strlen(var) + 1))
			{
				while (ms->envp[i])
				{
					ms->envp[i] = ms->envp[i + 1];
					i++;
				}
				break ;
			}
			free(var);
		}
	}
	ms->exit_status = 0;
}

void	call_export(t_minishell *ms, t_list *lst)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!lst->args[1])
	{
		while (ms->envp[i])
		{
			if (ft_strchr(ms->envp[i], '='))
			{
				tmp = ft_substr(ms->envp[i], 0, ft_strpos(ms->envp[i], "="));
				ft_printf("declare -x %s=\"%s\"\n",
					tmp, ft_strchr(ms->envp[i], '=') + 1);
				free(tmp);
			}
			else
				ft_printf("declare -x %s\n", ms->envp[i]);
			i++;
		}
	}
	else
		export2(ms, lst);
}

void	export2(t_minishell *ms, t_list *lst)
{
	int	i;
	int	j;

	j = 1;
	while (lst->args[j])
	{
		if (!ft_isalpha(lst->args[j][0]) && lst->args[j][0] != '_')
		{
			ft_printf("-minishell: export: `%s': not a valid identifier\n",
				lst->args[j]);
			ms->exit_status = 1;
			return ;
		}
		else
		{
			i = 0;
			while (ms->envp[i])
			{
				if (ms->envp[i + 1] == NULL)
				{
					ms->envp[i + 1] = ft_strdup(lst->args[j]);
					ms->envp[i + 2] = NULL;
					break ;
				}
				else if (ft_strncmp(ms->envp[i + 1], lst->args[j],
						ft_strpos(ms->envp[i + 1], "=") + 1) == 0)
				{
					ms->envp[i + 1] = ft_strdup(lst->args[j]);
					break ;
				}
				i++;
			}
		}
		j++;
	}
	ms->exit_status = 0;
}
