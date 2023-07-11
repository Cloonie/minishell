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

#include "minishell.h"

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
	int	i;

	i = -1;
	while (ms->input[++i])
		free(ms->input[i]);
	i = -1;
	free(ms->input);
	free(ms->token);
	while (*lst)
	{
		i = -1;
		while ((*lst)->cmd[++i])
			free((*lst)->cmd[i]);
		free((*lst)->infile);
		free((*lst)->outfile);
		(*lst) = (*lst)->next;
	}
}

void	myexit(int status)
{
	if (status == EXIT_SUCCESS)
		printf("EXIT_SUCCESS\n");
	else if (status == EXIT_FAILURE)
		printf("EXIT_FAILURE\n");
	system("leaks minishell");
	exit(status);
}

char	*ft_getenv(t_minishell *ms, char *envvar)
{
	char	*envval;
	int		i;

	i = 0;
	envval = NULL;
	while (ms->envp[++i])
	{
		if (!ft_strncmp(ft_substr(ms->envp[i], 0, ft_strpos(ms->envp[i], "=")),
				envvar, ft_strlen(envvar) + 1))
			envval = ft_strchr(ms->envp[i], '=') + 1;
	}
	return (envval);
}
