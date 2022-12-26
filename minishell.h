/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:54:27 by plau              #+#    #+#             */
/*   Updated: 2022/12/26 20:56:39 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/srcs/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <signal.h>
# include <termios.h>
# include <sys/wait.h>

/**
 * input = what user typed
 * cmd = aftersplit input
 * envp = list of envp
 * npath = number of path taken from $PATH 
 * hed = heredoc (whether there is two <<)
 * cmdc = cmd count
 */
typedef struct s_prg
{
	char	*input;
	char	**cmd;
	char	*cmdpath;
	char	**envp;
	int		npath;
	int		hed;
	int		cmdc;
}	t_prg;

void	init_struct(t_prg *prg);
void	shell_loop(t_prg *prg, char **envp);
void	setup_signal(void);

/* Parsing */
void	get_path(t_prg *prg, char **envp);
void	get_address(t_prg *prg);

/* Execution */
void	child_process(t_prg *prg, char **envp);

/* Helper functions */
void	exit_error(char *str);

#endif