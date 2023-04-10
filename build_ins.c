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

void	build_in(void)
{
	DIR				*dir;
	struct dirent	*entry;

	if (strcmp(input, "pwd") == 0)
		printf("%s\n", cwd);

	if (strcmp(input, "ls") == 0)
	{
		dir = opendir(cwd);
		while ((entry = readdir(dir)) != NULL)
			printf("%s\n", entry->d_name);
		closedir(dir);
	}

	if ((strcmp(input, "env") == 0))
		for (int i = 0; ev[i]; i++)
			printf("%s\n", ev[i]);

}
