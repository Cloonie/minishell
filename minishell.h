/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:36:33 by mliew             #+#    #+#             */
/*   Updated: 2023/06/05 15:36:28 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/stat.h>

# include "libft/includes/libft.h"
# include "libft/includes/ft_printf.h"
# include "libft/includes/get_next_line_bonus.h"

typedef struct s_minishell
{
	char	**input;
	int		*token;
	char	**envp;
	// char	**commands;
	// char	**operators;
}	t_minishell;

enum {
	TOK_EOF,
	TOK_CMD,
	TOK_ARG,
	TOK_REDIRECT,
	TOK_PIPE,
	TOK_DOLLAR,
	TOK_QUOTE,
	TOK_ESCAPE,
};

// main
char		**get_input(t_minishell *ms, char *cwd, char **envp);

// utils
void		sigint_handler(int sig);
void		myexit(int status);

// build_ins
void		call_echo(char **input);
void		call_cd(char **input, char *cwd);
void		call_unset(char **input, char **envp);
void		call_export(char **input, char **envp);
void		export2(char **input, char **envp);

// executable
void		call_env(char **envp);
void		call_run(char **input, char **envp);
int			cmd(char **input, char *cwd, char **ev);
int			executable(char **input, char **ev);

// lexer
// static int	count_words(char const *s);
// static char	*word_dup(const char *str, int start, int finish);
// static void	split_words(char **array, const char *s);
void		remove_quotes(char **array);
char		**lexer(char *s);

// parser 
char		**check_dollar(char **array, char **envp);
int			check_quotes(char *s);

// pipex
int			pipex(char **input, char **envp);

#endif