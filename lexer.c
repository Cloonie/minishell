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

#include "minishell.h"

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 2) * sizeof(char));
	while (start <= finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static void	split_words(char **array, const char *s, const char *op)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = -1;
	while (s[i])
	{
		k = i;
		if (i == 0 || s[i] != ' ')
		{
			if (s[i] == '\"')
				while (s[++i] && s[i] != '\"')
					;
			else if (s[i] == '\'')
				while (s[++i] && s[i] != '\'')
					;
			else
				while (!ft_strchr(op, s[i + 1])
					&& s[i + 1] != '\"' && s[i + 1] != '\"')
					i++;
			if (ft_strchr(op, s[k]) && s[k] != ' ')
			{
				if ((s[k] == '>' && s[k + 1] == '>')
					|| (s[k] == '<' && s[k + 1] == '<'))
				{
					k++;
					array[j++] = word_dup(s, k - 1, k);
					i++;
				}
				else
					array[j++] = word_dup(s, k, k);
				k++;
			}
			if (s[i] != ' ' && k <= i)
				array[j++] = word_dup(s, k, i);
		}
		i++;
	}
	array[j] = 0;
}

char	**lexer(char *s, const char *op)
{
	char		**array;
	int			size;
	int			i;

	size = 0;
	i = 0;
	if (!s)
		return (NULL);
	while (s[i++])
		if (ft_strchr(op, s[i]))
			size++;
	array = (char **)malloc(sizeof(char *) * (size) + 1);
	if (!array)
		return (NULL);
	if (check_quotes(s))
		return (array);
	split_words(array, s, op);
	return (array);
}
