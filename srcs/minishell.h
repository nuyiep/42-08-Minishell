/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:54:27 by plau              #+#    #+#             */
/*   Updated: 2023/03/17 12:56:21 by plau             ###   ########.fr       */
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

typedef struct s_exp
{
	char	**pair;
	char	*key;
	char	*value;
	int		quote;
}	t_exp;

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
	t_exp	*exp;
	int		npath;
	char	**path;
	int		no_pipes;
	int		heredoc;
	int		heredoc_postion;
	char	**av_execve;
}	t_prg;

/* Initialization */
void	init_struct(t_prg *prg, char **envp);
void	shell_loop(t_prg *prg, char **envp, char **av);
void	setup_signal(void);
int		read_command(t_prg *prg);

/* Parsing */

/* Executor */
int		executor(t_prg *prg, char **av, char **envp);
int		ms_heredoc(t_prg *prg);
void	do_pipex(t_prg *prg, char **envp);
void	get_path(t_prg *prg, char **envp);
void	find_npath(t_prg *prg);
void	cmd_access(t_prg *prg);
void	fork_process(t_prg *prg, char **envp, int **fd, int i);
void	fork_last_process(t_prg *prg, char **envp, int i);

/* Redirection- >, >>, < */
int		redirections(t_prg *prg, char **envp);
void	redirect_output(t_prg *prg, int i, char **envp);

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

/* lexer_utils */
int		has_pair(char *s);

/* lexer */
char	**split_token(t_prg *prg);

/* expand */
char	**expand_tokens(t_prg *prg);
char	*get_var(char *token, int i);

/* free */
void	free_exp(t_prg *prg, int value);

#endif