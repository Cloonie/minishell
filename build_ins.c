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

	i = 1;
	while (input[i++])
	{
		if (ft_strncmp(input[i], ft_strtrim("-n"), 2)) ft_
		{
			j = i;
			while (input[j + 1])

			printf("%s\n", input[i]);
			
		}
	}
}

void	build_in(char **input, char *cwd, char **ev)
{
	DIR				*dir;
	struct dirent	*entry;

	if (strcmp(input[0], "pwd") == 0)
		printf("%s\n", getcwd(cwd, sizeof(cwd)));

	if (strcmp(input[0], "echo") == 0)
		call_echo(input);

	if (strcmp(input[0], "ls") == 0)
	{
		dir = opendir(cwd);
		while ((entry = readdir(dir)) != NULL)
			printf("%s\n", entry->d_name);
		closedir(dir);
	}

	if ((strcmp(input[0], "env") == 0))
		for (int i = 0; ev[i]; i++)
			printf("%s\n", ev[i]);

}
