/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:54:27 by plau              #+#    #+#             */
/*   Updated: 2023/03/29 14:16:49 by plau             ###   ########.fr       */
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

/*
	In need of refactoring:
	parser - DONE
	expand - DONE
	expand_utils - DONE
	lexer - DONE
	lexer_utils - DONE
	pipex
*/

/* Global errno is defined here */
int exit_code;

/**
 * quote:
 * 1 - single
 * 2 - double
 */
typedef struct s_exp
{
	char	**pair;
	char	*key;
	char	*value;
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
	int		cmd_pos;
}	t_prg;

/* Initialization */
void	init_struct(t_prg *prg);
void	shell_loop(t_prg *prg, char **envp);
void	setup_signal(void);
int		read_command(t_prg *prg);
void	init_envp(t_prg *prg, char **envp);

/* Executor */
int		executor(t_prg *prg);
int		ms_heredoc(t_prg *prg, char **av);
void	do_pipex(t_prg *prg);
char	*cmd_access(t_prg *prg, char *cmd_zero);
void	execute_first_cmd(t_prg *prg, int **fd, char **av_one, int i);
void	execute_middle_cmd(t_prg *prg, int **fd, char **av_middle, int i);
void	execute_last_cmd(t_prg *prg, int **fd, char **av_last, int i);
int		check_redirection_builtins(t_prg *prg, char **av, int **fd);
void	get_path(t_prg *prg, char **envp);
void	find_npath(t_prg *prg);

/* Redirection */
int		redirections(t_prg *prg);
int		redirect_output(t_prg *prg, int i, char **av, int **fd);
void	redirect_append(t_prg *prg, int i, char **av);
void	redirect_input(t_prg *prg, int i, char **av);

/* Builtins */
int		builtins(t_prg *prg, char **envp, char **av);
void	pwd(t_prg *prg);
void	env(t_prg *prg);
void	echo(t_prg *prg, char **av);
void	ms_export(t_prg *prg);
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
void	close_pipes(int **fd);
void	close_last(int **fd);

/* Nicholas */

/* variables */
int find_var(char *token, char *var);
void get_value(t_prg *prg, char *key);

/* lexer_utils */
int		has_pair_first(char *s);
int		has_pair(char *s);
int		has_operators(char c, char *op);

/* lexer */
char	**split_token(t_prg *prg);
int		count_tab(char *s);

/* lexer_copy */
char	*copy_token(char *s, char ***tab, int *check);
char	*copy_operator(char *s, char ***tab, int *check);
char	*copy_quoted(char *s, char ***tab, int *check);
char	*check_first_quote(char *s, char ***tab, int *check);

/* expand */
int 	is_question(t_prg *prg, char *key);
int		has_value(t_prg *prg, char *key, int i);
char	**expand_tokens(t_prg *prg);
char	*get_var(char *token, int i);

/* free */
void	free_exp(t_prg *prg, int value);

/* parser */
char	**remove_all_quotes(t_prg *prg);

#endif