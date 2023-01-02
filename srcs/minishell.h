/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:54:27 by plau              #+#    #+#             */
/*   Updated: 2023/01/02 18:40:18 by plau             ###   ########.fr       */
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
# include <fcntl.h>

typedef struct s_token
{
	char	**all_token;
	char	**all_cmd1;
	char	**all_cmd2;
	char	*cmd1;
	char	*cmd2;
	char	*arr_in;
	char	*arr_out;
	char	*pipe;
	char	*infile;
	char	*outfile;
}	t_token;

/**
 * input = what user typed
 * cmd = aftersplit input
 * envp = list of envp
 * npath = number of path taken from $PATH 
 * fd_in = fd number for infile
 * n_env = number of env lines
 * echo_f = echo flag
 */
typedef struct s_prg
{
	char	*input;
	char	*cmdpath1;
	char	*cmdpath2;
	char	**av;
	char	**envp;
	char	**ls_envp;
	int		ac;
	int		npath;
	int		fd_in;
	int		fd_out;
	int		fd[2];
	int		ccmd;
	int		n_env;
	int		echo_f;
	t_token	token;
}	t_prg;

void	init_struct(t_prg *prg, char **av, int ac, char **envp);
void	shell_loop(t_prg *prg, char **envp);
void	setup_signal(void);
int		read_command(t_prg *prg);

/* Parsing */
void	get_path(t_prg *prg, char **envp);
void	get_address(t_prg *prg);
void	init_token(t_prg *prg);

/* Execution */
void	create_child(t_prg *prg);
void	get_address_one(t_prg *prg);
void	get_address_two(t_prg *prg);

/* Builtins */
int		builtins(t_prg *prg);
void	pwd(t_prg *prg);
void	env(t_prg *prg);
void	echo(t_prg *prg, char **av);
void	export(t_prg *prg);
int		check_flag(char *arg);

/* Helper functions */
void	error_nl(t_prg *prg, char *str);

/* Initialize */
void	check_open(t_prg *prg);



#endif