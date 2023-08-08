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

void	sigint_handler(int sig)
{
	(void)sig;
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_free(t_minishell	*ms, t_list **lst)
{
	// t_list	*tmp;
	int		i;

	i = -1;
	(void)lst;
	// tmp = *lst;
	while (ms->input[++i])
		free(ms->input[i]);
	free(ms->input);
	// free(ms->token);
	// while (tmp && tmp->args)
	// {
	// 	free(tmp->args);
	// 	tmp = tmp->next;
	// }
}

void	myexit(t_minishell	*ms, t_list **lst, int status)
{
	ft_free(ms, lst);
	free(lst);
	free(ms);
	if (status == EXIT_SUCCESS)
		printf("EXIT_SUCCESS\n");
	else if (status == EXIT_FAILURE)
		printf("EXIT_FAILURE\n");
	// system("leaks minishell");
	exit(status);
}

char	*ft_getenv(t_minishell *ms, char *envvar)
{
	char	*envval;
	char	*var;
	int		i;

	i = 0;
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
