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

void	get_input(t_minishell *ms)
{
	char	*line;
	char	*trim;
	char	tmp[100];

	getcwd(ms->cwd, sizeof(ms->cwd));
	ft_strlcpy(tmp, "\033[38;5;39m[minishell] \033[4;36m", 30);
	ft_strlcat(tmp, ms->cwd, 100);
	ft_strlcat(tmp, "\033[0;36m> \033[0m", 100);
	line = readline(tmp);
	if (!line)
		exit(0);
	if (ft_strncmp(line, "", 1))
		add_history(line);
	trim = ft_strtrim(line, " ");
	ms->input = lexer(trim, " ><|");
	ms->exit_status = 0;
	free(trim);
	free(line);
}

void	split_cmd(t_list **lst, t_minishell *ms)
{
	char	**tmp;
	int		i;
	int		j;

	i = -1;
	j = -1;
	tmp = (char **)malloc(MAX_BUF);
	while (ms->input[++i])
	{
		if (!ft_strncmp(ms->input[i], "|", 1))
		{
			tmp[++j] = NULL;
			ft_lstadd_back(lst, ft_lstnew(tmp));
			j = -1;
			while (tmp[++j])
				free(tmp[j]);
			free(tmp);
			tmp = (char **)malloc(MAX_BUF);
			j = -1;
		}
		else
			tmp[++j] = ft_strdup(ms->input[i]);
	}
	tmp[++j] = NULL;
	ft_lstadd_back(lst, ft_lstnew(tmp));
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*ms;
	t_list		**lst;

	ms = malloc(sizeof(t_minishell));
	lst = malloc(sizeof(t_list));
	ms->envp = envp;
	if (argv[1] || argc > 1)
		myexit(ms, lst, 1);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
	while (1)
	{
		get_input(ms);
		// get_token(ms);
		if (!check_quotes(ms))
		{
			remove_quotes(ms);
			check_dollar(ms);
			check_emptystr(ms);
			split_cmd(lst, ms);
			if (!redir(ms, lst))
				pipex(ms, lst);
		}
		ft_free(ms, lst);
		// while (*lst)
		// {
		// 	printf("NODE\n");
		// 	for (int x = 0; (*lst)->args[x]; x++)
		// 		printf("lst->args[%d]: %s\n", x, (*lst)->args[x]);
		// 	*lst = (*lst)->next;
		// }
		// for (int i = 0; ms->input[i]; i++)
		// 	printf("input[%d]: [%s] token:[%i]\n", i , ms->input[i], ms->token[i]);
		// for (int i = 0; ms->input[i]; i++)
		// 	printf("input[%d]: [%s]\n", i , ms->input[i]);
		// myexit(ms, lst, 0);
	}
}