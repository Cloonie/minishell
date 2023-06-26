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

#include <stdio.h>
#include <string.h>
#include <ctype.h>

static int	count_words(char const *s)
{
	int			words;

	words = 0;
	while (*s)
	{
		if (*s != ' ')
		{
			++words;
			while (*s && (*s != ' '))
				++s;
		}
		else
			++s;
	}
	return (words);
}

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));

	while (start <= finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

// static void	split_words(char **array, const char *s)
// {
// 	int			i;
// 	int			j;
// 	int			k;
// 	const char	*operators;
// 	char		temp[2];

// 	operators = "><$|";
// 	i = 0;
// 	j = 0;
// 	k = -1;
// 	while (i <= ft_strlen(s))
// 	{
// 		if (s[i] != ' ' && k < 0)
// 			k = i;
// 		else if ((!s[i] || s[i] == ' ') && k >= 0)
// 		{
// 			array[j++] = word_dup(s, k, i);
// 			k = -1;
// 		}
// 		else if ((s[i - 1] == '\'' || s[i - 1] == '\"'
// 				|| ft_strchr(operators, s[i])) && k >= 0)
// 		{
// 			array[j++] = word_dup(s, k, --i);
// 			if (ft_strchr(operators, s[++i]) && s[i] != '$')
// 			{
// 				temp[0] = s[i];
// 				temp[1] = '\0';
// 				array[j++] = ft_strdup(temp);
// 			}
// 			else
// 				i--;
// 			k = -1;
// 		}
// 		if (s[i] == '\"' && k >= 0)
// 			while (s[++i] && s[i] != '\"')
// 				;
// 		else if (s[i] == '\'' && k >= 0)
// 			while (s[++i] && s[i] != '\'')
// 				;
// 		i++;
// 	}
// 	array[j] = 0;
// }

static void	split_words(char **array, const char *s)
{
	int			i;
	int			j;
	int			k;
	const char	*operators;

	operators = " ><$|";
	i = 0;
	j = 0;
	k = -1;
	while (s[i])
	{
		k = i;
		if (s[i] != ' ')
		{
			if (s[i] == '\"')
				while (s[++i] && s[i] != '\"')
					;
			else if (s[i] == '\'')
				while (s[++i] && s[i] != '\'')
					;
			else
				while (!ft_strchr(operators, s[i + 1]))
					i++;
			if (ft_strchr(operators, s[k]) && s[k] != '$')
			{
				if (s[k] != ' ')
				{
					if ((s[k] == '>' && s[k + 1] == '>')
						|| (s[k] == '<' && s[k + 1] == '<'))
					{
						array[j++] = word_dup(s, k, k + 1);
						i++;
					}
					else
						array[j++] = word_dup(s, k, k);
				}
				k++;
			}
			if (s[i] != ' ' && k < i)
				array[j++] = word_dup(s, k, i);
		}
		i++;
	}
	array[j] = 0;
}

int	check_quotes(char *s)
{
	int	i;
	int	d_quote;
	int	s_quote;

	i = -1;
	d_quote = 0;
	s_quote = 0;
	while (s[++i])
	{
		if (s[i] == '\"')
			d_quote++;
		if (s[i] == '\'')
			s_quote++;
	}
	if ((d_quote % 2) != 0 || (s_quote % 2) != 0)
	{
		printf("Error quotes are not closed.\n");
		return (1);
	}
	return (0);
}

char	**lexer(char *s)
{
	char	**array;

	if (!s)
		return (NULL);
	array = malloc((count_words(s) + 100) * sizeof(char *));
	if (!array)
		return (NULL);
	check_quotes(s);
	split_words(array, s);
	return (array);
}
