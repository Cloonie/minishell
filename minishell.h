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

typedef	struct s_pipe {
	int		numcmd;
	int		tmpin;
	int		tmpout;
	int		here_doc_flag;
	int		tmp;
}	t_pipe;

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
	TOK_REDIRECT,
	TOK_PIPE,
	TOK_DOLLAR,
	TOK_QUOTE,
	TOK_ESCAPE,
};

// main
char		**get_input(t_minishell *ms);

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
int			cmd(t_minishell *ms, int i);
int			executable(char **input, char **envp , int i);

// lexer
// static int	count_words(char const *s);
// static char	*word_dup(const char *str, int start, int finish);
// static void	split_words(char **array, const char *s);
void		remove_quotes(char **array);
char		**lexer(char *s);

// parser
void		check_spaces(t_minishell *ms);
char		**check_dollar(char **array, char **envp);
int			check_quotes(char *s);

// pipex
// int			pipex(char **input, char **envp);
void		handle_pipe(t_minishell *ms);
int			fork_process(t_pipe *pipe_vars, t_minishell *ms);
int			parent_wait(t_pipe *pipe_vars);

#endif