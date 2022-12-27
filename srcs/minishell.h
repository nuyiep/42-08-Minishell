/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:54:27 by plau              #+#    #+#             */
/*   Updated: 2022/12/27 21:49:40 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/srcs/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <sys/wait.h>

/**
 * input = what user typed
 * cmd = aftersplit input
 * envp = list of envp
 * npath = number of path taken from $PATH 
 */
typedef struct s_prg
{
	char	*input;
	char	*cmdpath;
	char	**av;
	char	**cmd;
	char	**envp;
	char	**ls_envp;
	int		ac;
	int		npath;
	int		fd_in;
}	t_prg;

enum
{
	T_ARROWIN,
	T_ARROWOUT,
	T_PIPE,
	T_CMD,
	T_MSG,
	T_HEREDOC,
	T_APPENDOUT
}	e_type;

void	init_struct(t_prg *prg, char **av, int ac, char **envp);
void	shell_loop(t_prg *prg, char **envp);
void	setup_signal(void);

/* Parsing */
void	get_path(t_prg *prg, char **envp);
void	get_address(t_prg *prg);
void	ms_parse(t_prg *prg);

/* Execution */
void	child_process(t_prg *prg, char **envp);

/* Builtins */
void	builtins(t_prg *prg);
void	pwd(t_prg *prg);
void	print_env(t_prg *prg);

/* Helper functions */
void	exit_error(char *str);

#endif