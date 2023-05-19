/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:31:58 by mliew             #+#    #+#             */
/*   Updated: 2023/05/19 14:34:32 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum {
	TOK_SPACE,
	TOK_BACKSLASH,
	TOK_SEMICOLON,
	TOK_SINGLEQ,
	TOK_DOUBLEQ,
	TOK_DOLLAR,
	TOK_REDIRECT_LEFT,
	TOK_REDIRECT_RIGHT,
	TOK_APPEND_LEFT,
	TOK_APPEND_RIGHT,
	TOK_PIPE,
	TOK_EOF,
};

// void	token(char **input)
// {
// 	int	i;

// 	i = 0;
// 	while (input)
// 	{
// 		if (input[i][0] == '\"' && input[i][ft_strlen(input[i])] == '\"')
// 			ft_strtrim(input[i], "\"");
// 	}
// }

static int	count_words(char const *s, char c)
{
	int		words;

	words = 0;
	while (*s)
	{
		if (*s != c)
		{
			++words;
			while (*s && *s != c)
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
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static void	split_words(char **array, const char *s, char c)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && k < 0)
			k = i;
		else if ((s[i] == c || i == ft_strlen(s)) && k >= 0)
		{
			array[j++] = word_dup(s, k, i);
			k = -1;
		}
		i++;
	}
	array[j] = 0;
}

char	**lexer(char const *s, char c)
{
	char	**array;

	if (!s)
		return (NULL);
	array = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	split_words(array, s, c);
	return (array);
}
