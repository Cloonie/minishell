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

// t_list	*array2list(char **array)
// {
// 	t_list	**list;
// 	int		i;

// 	i = -1;
// 	while (array[++i])
// 	{
// 		list = ft_lstnew(array[i]);
// 		// list->token = tokenize(array[i]);
// 		list = list->next;
// 	}
// 	return (list);
// }

char **get_input(char *cwd, char **envp)
{
	// t_list	*list;
	char	*input;
	char	**av;

	input = readline(ft_strjoin(ft_strjoin
				("\033[38;5;39m[minishell] \033[4;36m", cwd),
				"\033[0;36m> \033[0m"));
	if (input == NULL)
		exit(0);
	ft_strtrim(input, " ");
	add_history(input);
	av = lexer(input);
	av = check_dollar(av, envp);
	// list = array2list(av);
	return (av);
}

int	main(int argc, char **argv, char **envp)
{
	// t_list	*list;
	char	**input;
	char	cwd[1024];

	if (!argv[0] || argc != 1)
		myexit(1);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		getcwd(cwd, sizeof(cwd));
		input = get_input(cwd, envp);
		cmd(input, cwd, envp);
		// printf("VAR: %s TOKEN: %d QUOTED: %d\n", list->var, list->token, list->quoted);
		// printf("%s", list->var);
	}
}

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