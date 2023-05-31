/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:31:58 by mliew             #+#    #+#             */
/*   Updated: 2023/05/31 18:36:36 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum {
	TOK_EOF,
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
};

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	count_words(char const *s)
{
	int		words;

	words = 0;
	while (*s)
	{
		if (*s != ' ')
		{
			++words;
			while (*s && *s != ' ')
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

int	is_special_char(char c)
{
	if (c == ' ')
		return (TOK_SPACE);
	else if (c == '\"')
		return (TOK_DOUBLEQ);
	else if (c == '\'')
		return (TOK_SINGLEQ);
	else if (c == '>')
		return (TOK_REDIRECT_RIGHT);
	else if (c == '<')
		return (TOK_REDIRECT_LEFT);
	else if (c == '$')
		return (TOK_DOLLAR);
	else if (c == '|')
		return (TOK_PIPE);
	else
		return (TOK_EOF);
}

static void	split_words(char **array, const char *s)
{
	int		i; // string index
	int		j; // array index
	int		k; // start index

	i = 0;
	j = 0;
	k = -1;
	while (i <= ft_strlen(s))
	{
		if (!is_special_char(s[i]) && k < 0)
			k = i;
		else if ((is_special_char(s[i]) == TOK_SPACE || i == ft_strlen(s)) && k >= 0)
		{
			array[j++] = word_dup(s, k, i);
			k = -1;
		}
		else if (is_special_char(s[i]) == TOK_DOUBLEQ)
		{
			k = i;
			while (s[++i])
			{
				if (!s[i])
					exit(0);
				if (s[i] == '\"')
					break ;
			}
			// array[j++] = word_dup(s, k, i);
		}
		i++;
	}
	array[j] = 0;
}

char	**lexer(char const *s)
{
	char	**array;

	if (!s)
		return (NULL);
	array = malloc((count_words(s) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	split_words(array, s);
	return (array);
}

int	main()
{
	char	**array;

	array = lexer("Hello, \"how are\" you?");
	for (int i = 0; array[i]; i++)
		printf("String %d: |%s|\n", i, array[i]);
	system("leaks a.out");
	// printf("%d\n", is_special_char('\"'));
}
