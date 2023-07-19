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

#include "minishell.h"

void	call_echo(t_list *lst)
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
		printf("%s", lst->args[i]);
		if (lst->args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}

void	call_cd(t_minishell *ms, t_list *lst)
{
	char	*path;

	if (lst->args[1] && lst->args[1][0] == '/')
	{
		if (chdir(lst->args[1]) == 0)
			;
		else
			printf("%s: %s: No such file or directory\n", lst->args[0], lst->args[1]);
	}
	else if (lst->args[1])
	{
		path = ft_strjoin(ft_strjoin(ms->cwd, "/"), lst->args[1]);
		if (chdir(path) == 0)
			;
		else
			printf("%s: %s: No such file or directory\n", lst->args[0], lst->args[1]);
	}
	else
		chdir(ft_getenv(ms, "HOME"));
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
		}
	}
}

void	call_export(t_minishell *ms, t_list *lst)
{
	int	i;

	i = -1;
	if (!lst->args[1])
	{
		while (ms->envp[++i])
		{
			if (ft_strchr(ms->envp[i], '='))
				printf("declare -x %s=\"%s\"\n",
					ft_substr(ms->envp[i], 0, ft_strpos(ms->envp[i], "=")),
					ft_strchr(ms->envp[i], '=') + 1);
			else
				printf("declare -x %s\n", ms->envp[i]);
		}
	}
	export2(ms, lst);
}

void	export2(t_minishell *ms, t_list *lst)
{
	int	i;
	int	j;

	j = 1;
	while (lst->args[j])
	{
		if (!ft_isalpha(lst->args[j][0]))
			printf("-minishell: export: `%s': not a valid identifier\n",
				lst->args[j]);
		else
		{
			i = -1;
			while (ms->envp[++i])
			{
				if (ms->envp[i + 1] == NULL)
				{
					ms->envp[i + 1] = lst->args[j];
					ms->envp[i + 2] = NULL;
					break ;
				}
				else if (ft_strncmp(ms->envp[i + 1], lst->args[j],
						ft_strpos(ms->envp[i + 1], "=") + 1) == 0)
				{
					ms->envp[i + 1] = lst->args[j];
					break ;
				}
			}
		}
		j++;
	}
}
