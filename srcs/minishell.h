/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:54:27 by plau              #+#    #+#             */
/*   Updated: 2023/03/03 19:26:40 by plau             ###   ########.fr       */
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

/**
 * input = what user typed
 * ls_envp = a copy of envp
 * all_token = ft_split(input)
 */
typedef struct s_prg
{
	char	*input;
	char	**ls_envp;
	char	**all_token;
}	t_prg;

/* Initialization */
void	init_struct(t_prg *prg, char **av, int ac, char **envp);
void	shell_loop(t_prg *prg, char **envp, char **av);
void	setup_signal(void);
int		read_command(t_prg *prg);

/* Parsing */

/* Executor */
int		executor(t_prg *prg, char **av, char **envp);
void	heredoc_main(t_prg *prg, char **av, char **envp);

/* Builtins */
int		builtins(t_prg *prg, char **envp);
void	pwd(t_prg *prg);
void	env(t_prg *prg);
void	echo(t_prg *prg, char **av);
void	export(t_prg *prg);
int		check_flag(char *arg);
void	cd(t_prg *prg, char **envp);
int		key_exist(t_prg *prg, char *key);
void	update_key(t_prg *prg, char *arg, char *key);
void	declare_x(t_prg *prg);
char	**separate_key_value(char *arg);
void	add_key(t_prg *prg, char *str);
void	unset(t_prg *prg);
void	ms_exit(t_prg *prg);

/* Helper functions */
void	error_nl(t_prg *prg, char *str);

/* Nicholas */
char *expand(t_prg *prg, char *key);

#endif