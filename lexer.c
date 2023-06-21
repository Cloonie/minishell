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
	const char	*operators;

	operators = "\"\'><$|";
	words = 0;
	while (*s)
	{
		if (*s != ' ' || ft_strchr(operators, *s))
		{
			++words;
			while (*s && (*s != ' ' || ft_strchr(operators, *s)))
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
	word = malloc((finish - start + 2) * sizeof(char));

	while (start <= finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static void	split_words(char **array, const char *s)
{
	int		i; // string index
	int		j; // array index
	int		k; // start index
	const char	*operators;

	operators = "\"\'><$|";
	i = 0;
	j = 0;
	k = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != ' ' && k < 0)
			k = i;
		else if ((!s[i + 1] || s[i + 1] == ' ' || ft_strchr(operators, s[i + 1])) && k >= 0)
		{
			array[j++] = word_dup(s, k, i);
			k = -1;
		}
		if (s[i] == '\"')
			while (s[++i] && s[i] != '\"')
				;
		else if (s[i] == '\'')
			while (s[++i] && s[i] != '\'')
				;
		i++;
	}
	array[j] = 0;
}

char	**check_dollar(char **array, char **envp)
{
	int		i;
	int		j;
	char	*str;
	char	*var;

	i = -1;
	while (array[++i])
	{
		j = -1;
		var = &array[i][1];
		while (array[i][0] == '$' && envp[++j] && array[i][1])
		{
			str = ft_substr(envp[j], 0, ft_strpos(envp[j], "="));
			if (ft_strncmp(str, var, ft_strlen(var) + 1) == 0)
				array[i] = ft_strchr(envp[j], '=') + 1;
			else if (!envp[j + 1])
				array[i] = "";
		}
	}
	return (array);
}

void	remove_quotes(char **array)
{
	int	i;

	i = 0;

	while (array[i])
	{
		if (array[i][0] == '\"'
				&& array[i][ft_strlen(array[i]) - 1] == '\"')
			array[i] = ft_strtrim(array[i], "\"");
		else if (array[i][0] == '\''
				&& array[i][ft_strlen(array[i]) - 1] == '\'')
			array[i] = ft_strtrim(array[i], "\'");
		i++;
	}
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
	array = malloc((count_words(s) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	check_quotes(s);
	split_words(array, s);
	for (int i = 0; array[i]; i++)
		printf("array[%d]: [%s]\n", i , array[i]);
	return (array);
}
