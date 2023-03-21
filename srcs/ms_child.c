/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:02:02 by plau              #+#    #+#             */
/*   Updated: 2023/03/21 11:59:42 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Finds the PATH where the command is located */
/* and executes it. Process ends when execve is successful */
/* Example: ls | ls | ls or  */
void	run_process(t_prg *prg, char **env, char **av)
{
	char	*first_arg;

	first_arg = av[0];
	if ((ft_strncmp(first_arg, "/", 1) != 0))
	{
		get_path(prg, env);
		find_npath(prg);
		first_arg = cmd_access(prg, first_arg);
	}
	execve(first_arg, av, env);
	error_nl(prg, first_arg);
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

	pid = fork();
	if (pid < 0)
		error_nl(prg, "Fork process");
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(fd[i][0]);
		dup2(fd[i][1], STDOUT_FILENO);
		run_process(prg, envp, av_one);
	}
	else
		close(fd[i][1]);
}

void	execute_middle_cmd(t_prg *prg, int **fd, char **envp, char **av_middle, int i)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		error_nl(prg, "Fork process");
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(fd[i][0]);
		close(fd[i - 1][1]);
		dup2(fd[i - 1][0], STDIN_FILENO);
		dup2(fd[i][1], STDOUT_FILENO);
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

	pid = fork();
	if (pid < 0)
		error_nl(prg, "Fork process");
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(fd[i - 1][1]);
		dup2(fd[i - 1][0], STDIN_FILENO);
		run_process(prg, envp, av_last);
	}
	else
		close(fd[i - 1][0]);
}
