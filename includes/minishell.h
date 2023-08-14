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

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line_bonus.h"

# define MAX_BUF 10000

typedef struct s_minishell
{
	char	**input;
	int		*token;
	char	**envp;
	char	cwd[1024];
	int		ori_in;
	int		ori_out;
	int		fdin;
	int		fdout;
	int		exit_status;
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
void		get_input(t_minishell *ms);

// utils
void		sigint_handler(int sig);
void		ft_free(t_minishell	*ms, t_list **lst);
void		myexit(t_minishell	*ms, t_list **lst, int status);
char		*ft_getenv(t_minishell *ms, char *envvar);
void		init_pipe(t_minishell *ms);

// build_ins
void		call_echo(t_minishell *ms, t_list *lst);
void		call_cd(t_minishell *ms, t_list *lst);
void		call_unset(t_minishell *ms, t_list *lst);
void		call_export(t_minishell *ms, t_list *lst);
void		export2(t_minishell *ms, t_list *lst);

// build_ins2
void		call_env(t_minishell *ms, t_list *lst);
void		call_run(t_minishell *ms, t_list *lst);

// executer
int			cmd(t_minishell *ms, t_list **lst);
int			executable(t_minishell *ms, t_list *lst);

// lexer
char		**lexer(char *s, const char *op);

// token
int			check_valid_cmd(t_minishell *ms, char *input);
void		get_token(t_minishell *ms);

// parser
void		remove_quotes(t_minishell *ms);
void		check_dollar(t_minishell *ms);
int			check_quotes(t_minishell *ms);
void		check_emptystr(t_minishell *ms);

// redirection
int			rm_2strs(t_list *tmp, int i);
int			redir_type(t_list *tmp, int i);
int			redir_error(t_minishell *ms, t_list *tmp, int i);
int			redir(t_minishell *ms, t_list **lst);

// pipe
void		pipex(t_minishell *ms, t_list **lst);

#endif