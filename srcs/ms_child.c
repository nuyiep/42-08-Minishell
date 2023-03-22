/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:02:02 by plau              #+#    #+#             */
/*   Updated: 2023/03/22 17:38:24 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Finds the PATH where the command is located */
/* and executes it. Process ends when execve is successful */
/* Example: ls | ls | ls or  */
void	run_process(t_prg *prg, char **env, char **av)
{
	if ((ft_strncmp(av[0], "/", 1) != 0))
		av[0] = cmd_access(prg, av[0]);
	execve(av[0], av, env);
	error_nl(prg, av[0]);
}

/* SIGINT - CONTROL C */
/* SIGQUIT - CONTROL \ */

/* Fork a process that executes the command */
/* As "execve" ends the calling process when successful, */
/* forking is necessary */
/* Do child will be divided into 3 processes */
/* 1. first_process- read from std out */
/* dprintf(2, "first process\n") */
/* first cmd - [unclosed] child will write */
/* 			 - child read end need to close */
/* 			 - parent write end need to close */
/*			 - [unclosed] parent read end - remain unclosed - for the next cmd to read from */
void	execute_first_cmd(t_prg *prg, int **fd, char **envp, char **av_one, int i)
{
	int	pid;

	if (check_redirection_builtins(prg, av_one, envp) == 1)
		return ;
	pid = fork();
	if (pid < 0)
		error_nl(prg, "Fork process");
	if (pid == 0)
	{
		close(fd[i][0]);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(fd[i][1], STDOUT_FILENO);
		run_process(prg, envp, av_one);
	}
	else
		close(fd[i][1]);
}

void	execute_middle_cmd(t_prg *prg, int **fd, char **envp, char **av_middle, int i)
{
	int	pid;

	if (check_redirection_builtins(prg, av_middle, envp) == 1)
		return ;
	pid = fork();
	if (pid < 0)
		error_nl(prg, "Fork process");
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(fd[i - 1][0], STDIN_FILENO);
		dup2(fd[i][1], STDOUT_FILENO);
		close(fd[i][0]);
		close(fd[i - 1][1]);
		run_process(prg, envp, av_middle);
	}
	else
	{
		close(fd[i][1]);
		close(fd[i - 1][0]);
	}
}

void	execute_last_cmd(t_prg *prg, int **fd, char **envp, char **av_last, int i)
{
	int		pid;

	if (check_redirection_builtins(prg, av_last, envp) == 1)
		return ;
	pid = fork();
	if (pid < 0)
		error_nl(prg, "Fork process");
	if (pid == 0)
	{
		close(fd[i - 1][1]);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(fd[i - 1][0], STDIN_FILENO);
		run_process(prg, envp, av_last);
	}
	else
		close(fd[i - 1][0]);
}
