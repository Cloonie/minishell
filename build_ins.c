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

void	call_echo(char **input)
{
	int	i;
	int	j;
	int	newline;

	i = 1;
	j = 1;
	newline = 1;
	while (input[i])
	{
		if (input[i][j - 1] != '-')
			break ;
		while (input[i][j])
		{
			if (i == 1 && input[i][j] == 'n' && !input[i][j + 1])
				newline = 0;
			else if (input[i][j] != 'n')
				break ;
			j++;
		}
		if (input[i][j] && input[i][j] != 'n')
			break ;
		j = 1;
		i++;
	}
	while (input[i])
	{
		printf("%s", input[i]);
		if (input[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}

void	call_cd(char **input, char *cwd)
{
	char	*path;

	if (input[1] && input[1][0] == '/')
	{
		if (chdir(input[1]) == 0)
			;
		else
			printf("%s: %s: No such file or directory\n", input[0], input[1]);
	}
	else if (input[1])
	{
		path = ft_strjoin(ft_strjoin(cwd, "/"), input[1]);
		if (chdir(path) == 0)
			;
		else
			printf("%s: %s: No such file or directory\n", input[0], input[1]);
	}
	else
		chdir(getenv("HOME"));
}

void	call_unset(char **input, char **envp)
{
	char	*var;
	int		i;
	int		j;

	if (!input[1])
		return ;
	j = 0;
	while (input[++j])
	{
		i = -1;
		while (envp[++i])
		{
			if (ft_strpos(envp[i], "="))
				var = ft_substr(envp[i], 0, ft_strpos(envp[i], "="));
			else
				var = ft_substr(envp[i], 0, ft_strlen(envp[i]));
			if (!ft_strncmp(input[j], var, ft_strlen(var) + 1))
			{
				while (envp[i])
				{
					envp[i] = envp[i + 1];
					i++;
				}
				break ;
			}
		}
	}
}

void	call_export(char **input, char **envp)
{
	int	i;

	i = -1;
	if (!input[1])
	{
		while (envp[++i])
		{
			if (ft_strchr(envp[i], '='))
				printf("declare -x %s=\"%s\"\n",
					ft_substr(envp[i], 0, ft_strpos(envp[i], "=")),
					ft_strchr(envp[i], '=') + 1);
			else
				printf("declare -x %s\n", envp[i]);
		}
	}
	export2(input, envp);
}

void	export2(char **input, char **envp)
{
	int	i;
	int	j;

	j = 1;
	while (input[j])
	{
		if (!ft_isalpha(input[j][0]))
			printf("-minishell: export: `%s': not a valid identifier\n",
				input[j]);
		else
		{
			i = -1;
			while (envp[++i])
			{
				if (envp[i + 1] == NULL)
				{
					envp[i + 1] = input[j];
					envp[i + 2] = NULL;
					break ;
				}
				else if (ft_strncmp(envp[i + 1], input[j],
					ft_strpos(envp[i + 1], "=") + 1) == 0)
				{
					envp[i + 1] = input[j];
					break ;
				}
			}
		}
		j++;
	}
}

// void	call_ls(void)
// {
// 	DIR				*dir;
// 	struct dirent	*entry;
// 	if (strcmp(input[0], "ls") == 0)
// 	{
// 		dir = opendir(cwd);
// 		while ((entry = readdir(dir)) != NULL)
// 			printf("%s\n", entry->d_name);
// 		closedir(dir);
// 	}
// }
