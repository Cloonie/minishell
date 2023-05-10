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

void	ctrl(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		// rl_replace_line("", 0);mak
		rl_redisplay();
	}
}

char	**get_input(char *cwd)
{
	char	*input;
	char	**av;

	input = readline(ft_strjoin(ft_strjoin("MK42@minishell:", cwd), "> "));
	if (input == NULL)
		exit (0);
	ft_strtrim(input, " ");
	av = ft_split(input, ' ');
	add_history(input);
	return (av);
}

int	main(int argc, char **argv, char **envp)
{
	char	**input;
	char	cwd[1024];
	// t_list	*env;

	// int i = 0;
	// while (envp[i])
	// {
	// 	ft_lstadd_back(&env, ft_lstnew(envp[i++]));
	// }
	// while (env)
	// {
	// 	printf("%s\n", env->var);
	// 	env = env->next;
	// }

	(void)argc;
	(void)argv;
	(void)envp;
	signal(SIGINT, ctrl);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		getcwd(cwd, sizeof(cwd));
		input = get_input(cwd);
		build_in(input, cwd, envp);
	}
	// rl_clear_history();
	free(input);
	return (0);
}
