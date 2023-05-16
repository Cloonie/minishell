/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:36:33 by mliew             #+#    #+#             */
/*   Updated: 2023/05/15 15:51:44 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/stat.h>
# include <string.h>

# include "libft/includes/libft.h"
# include "libft/includes/ft_printf.h"
# include "libft/includes/get_next_line_bonus.h"

// # define Ctrl(x) ((x) & 0x1f)

// main
char	**get_input(char *cwd);

// utils
void	sigint_handler(int sig);

// executable
void	executable(char **input, char **ev);

// cmd
void	cmd(char **input, char *cwd, char **ev);

#endif