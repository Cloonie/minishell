/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 00:07:08 by mliew             #+#    #+#             */
/*   Updated: 2023/04/04 00:07:08 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free2(t_list *current)
{
	int		i;

	i = -1;
	while (current->args[++i])
		free(current->args[i]);
	free(current->args);
	if (current->infile)
		free(current->infile);
	if (current->outfile)
		free(current->outfile);
	if (current->delimiter)
		free(current->delimiter);
	free(current);
}

void	ft_free(t_minishell *ms, t_list **lst)
{
	t_list	*next;
	t_list	*current;
	int		i;

	i = -1;
	if (ms->input)
	{
		while (ms->input[++i])
			free(ms->input[i]);
		free(ms->input);
	}
	current = *lst;
	while (current)
	{
		next = current->next;
		ft_free2(current);
		current = next;
	}
	*lst = NULL;
}

void	myexit(t_minishell	*ms, t_list **lst)
{
	ft_free(ms, lst);
	free(lst);
	free(ms);
	exit(ms->exit_status);
}
// system("leaks minishell");

char	*ft_getenv(t_minishell *ms, char *envvar)
{
	char	*envval;
	char	*var;
	int		i;

	i = -1;
	envval = NULL;
	if (!ft_strncmp(envvar, "?\0", 2))
		return (ft_itoa(ms->exit_status));
	while (ms->envp[++i])
	{
		var = ft_substr(ms->envp[i], 0, ft_strpos(ms->envp[i], "="));
		if (!ft_strncmp(var, envvar, ft_strlen(envvar) + 1))
			envval = ft_strchr(ms->envp[i], '=') + 1;
		free(var);
	}
	return (envval);
}

void	init_pipe(t_minishell *ms)
{
	ms->ori_in = dup(0);
	ms->ori_out = dup(1);
	ms->fdin = 0;
	ms->fdout = 0;
}
