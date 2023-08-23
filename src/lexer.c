/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:31:58 by mliew             #+#    #+#             */
/*   Updated: 2023/06/05 16:45:30 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	split_helper(char **array, const char *s, const char *op, int i[3])
{
	if ((s[i[0]] == ' ' || i[0] == ft_strlen(s)
			|| (s[i[0]] && ft_strchr(op, s[i[0]])))
		&& i[2] >= 0)
	{
		if ((i[0] - i[2]) != 0)
			array[++i[1]] = ft_substr(s, i[2], i[0] - i[2]);
		if (s[i[0]] && ft_strchr(op, s[i[0]]))
		{
			i[2] = i[0];
			if ((s[i[0]] == '>' && s[i[0] + 1] == '>')
				|| (s[i[0]] == '<' && s[i[0] + 1] == '<'))
			{
				array[++i[1]] = ft_substr(s, i[2], 2);
				i[0]++;
			}
			else
				array[++i[1]] = ft_substr(s, i[2], 1);
		}
		i[2] = -1;
	}
}

int	split_words(char **array, const char *s, const char *op)
{
	int	i[3];

	i[0] = -1;
	i[1] = -1;
	i[2] = -1;
	while (++i[0] <= ft_strlen(s))
	{
		if (s[i[0]] != ' ' && i[2] < 0)
			i[2] = i[0];
		if (s[i[0]] == '\"')
			while (s[++i[0]] && s[i[0]] != '\"')
				;
		else if (s[i[0]] == '\'')
			while (s[++i[0]] && s[i[0]] != '\'')
				;
		split_helper(array, s, op, i);
	}
	array[++i[1]] = NULL;
	return (i[1]);
}

char	**lexer(char *s, const char *op)
{
	int		size;
	int		i;
	char	**array;

	i = -1;
	if (!s)
		return (NULL);
	array = malloc(sizeof(char *) * MAX_BUF);
	size = split_words(array, s, op);
	while (array[++i])
		free(array[i]);
	free(array);
	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	split_words(array, s, op);
	return (array);
}
