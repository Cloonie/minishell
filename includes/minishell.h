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
# include <termios.h>

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line_bonus.h"

# define MAX_BUF 10000

typedef struct s_minishell
{
	char			**input;
	int				*token;
	char			**envp;
	char			cwd[1024];
	int				ori_in;
	int				ori_out;
	int				fdin;
	int				fdout;
	int				exit_status;
	int				quote;
	struct termios	new_attr;
	struct termios	ori_attr;
}	t_minishell;

// main
void		get_input(t_minishell *ms);
void		split_cmd(t_list **lst, t_minishell *ms);

// utils
void		ft_free2(t_list *current);
void		ft_free(t_minishell	*ms, t_list **lst);
void		myexit(t_minishell	*ms, t_list **lst);
char		*ft_getenv(t_minishell *ms, char *envvar);
void		init_pipe(t_minishell *ms);

// build_ins
void		call_echo2(t_minishell *ms, t_list *lst, int i, int newline);
void		call_echo(t_minishell *ms, t_list *lst);
void		call_cd(t_minishell *ms, t_list *lst);
void		call_env(t_minishell *ms, t_list *lst);
void		call_run(t_minishell *ms, t_list *lst);

// build_ins2
void		call_unset2(t_minishell *ms, t_list *lst, int j);
void		call_unset(t_minishell *ms, t_list *lst);
void		call_export(t_minishell *ms, t_list *lst);
void		export2(t_minishell *ms, t_list *lst);
void		export3(t_minishell *ms, t_list *lst, int i, int j);

// executer
int			check_build_ins(t_list **lst);
int			run_build_ins(t_minishell *ms, t_list **lst);
int			cmd(t_minishell *ms, t_list **lst);
int			fork_pid(t_minishell *ms, t_list *lst, char **paths, int i);
int			executable(t_minishell *ms, t_list *lst);

// lexer
void		split_helper(char **array, const char *s, const char *op, int i[3]);
int			split_words(char **array, const char *s, const char *op);
char		**lexer(char *s, const char *op);

// dollar
void		check_dollar(t_minishell *ms);
void		check_dollar2(t_minishell *ms, char *temp, char *result, int i[3]);
void		check_dollar3(t_minishell *ms, char *temp, char *result, int i[3]);
void		check_dollar4(t_minishell *ms, char *temp, char *result, int i[3]);

// parser
int			check_quotes(t_minishell *ms);
int			check_quotes2(t_minishell *ms, int quoted);
void		check_emptystr(t_minishell *ms);

// signal
void		signal_handler(int num);

// redirection
int			rm_2strs(t_list *tmp, int i);
int			redir_type(t_list *tmp, int i);
int			redir_error(t_minishell *ms, t_list *tmp, int i);
int			redir(t_minishell *ms, t_list **lst);

// pipe
void		stdio_readline(t_minishell *ms);
void		here_doc(t_minishell *ms, t_list **lst);
int			input(t_minishell *ms, t_list **lst);
void		output(t_minishell *ms, t_list **lst);

// final
void		final(t_minishell *ms, t_list **lst);
void		child_loop(t_minishell *ms, t_list **lst, int i, pid_t *child);
void		child_run(t_minishell *ms, t_list **lst);

#endif