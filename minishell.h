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
	char	cwd[1024];
}	t_minishell;

enum {
	TOK_EOF,
	TOK_CMD,
	TOK_ARG,
	TOK_SQUOTE,
	TOK_DQUOTE,
	TOK_DOLLAR,
	TOK_REDIRECT,
	TOK_PIPE,
	TOK_ESCAPE,
};

// main
char		**get_input(t_minishell *ms);

// utils
void		sigint_handler(int sig);
void		myexit(int status);
char		*ft_getenv(t_minishell *ms, char *envvar);

// build_ins
void		call_echo(char **input);
void		call_cd(char **input, char *cwd);
void		call_unset(char **input, char **envp);
void		call_export(char **input, char **envp);
void		export2(char **input, char **envp);

// build_ins2
void		call_env(char **envp);
void		call_run(char **input, char **envp);


// executer
int			cmd(t_minishell *ms);
int			executable(t_minishell *ms, char **input, char **envp);

// lexer
char		**lexer(char *s, const char *op);

// token
int			check_valid_cmd(t_minishell *ms, char *input);
void		get_token(t_minishell *ms);

// parser
void		remove_quotes(char **array);
void		check_dollar(t_minishell *ms);
int			check_quotes(char *s);
void		check_emptystr(t_minishell *ms);

// pipex
int			pipex(char **input, char **envp);

#endif