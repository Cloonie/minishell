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

void	call_unset2(t_minishell *ms, t_list *lst, int j)
{
	char	*var;
	int		i;

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
				free(ms->envp[i]);
				ms->envp[i] = ms->envp[i + 1];
				i++;
			}
			free(var);
			break ;
		}
		free(var);
	}
}

void	call_unset(t_minishell *ms, t_list *lst)
{
	int		j;

	if (!lst->args[1])
		return ;
	j = 0;
	while (lst->args[++j])
		call_unset2(ms, lst, j);
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

	i = 0;
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
			export3(ms, lst, i, j);
		j++;
	}
	ms->exit_status = 0;
}

void	export3(t_minishell *ms, t_list *lst, int i, int j)
{
	i = 0;
	while (ms->envp[i])
	{
		if (ms->envp[i + 1] == NULL)
		{
			free(ms->envp[i + 1]);
			ms->envp[i + 1] = ft_strdup(lst->args[j]);
			ms->envp[i + 2] = NULL;
			break ;
		}
		else if (!ft_strncmp(ms->envp[i + 1], lst->args[j],
				ft_strpos(ms->envp[i + 1], "=") + 1))
		{
			free(ms->envp[i + 1]);
			ms->envp[i + 1] = ft_strdup(lst->args[j]);
			break ;
		}
		i++;
	}
}
