/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:02:02 by plau              #+#    #+#             */
/*   Updated: 2023/03/18 15:25:55 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Finds the PATH where the command is located */
/* and executes it. Process ends when execve is successful */
/* Example: ls | ls | ls or  */
void	run_process(t_prg *prg, char **env, int start)
{
	if ((ft_strncmp(prg->av_execve[start], "/", 1) != 0))
	{
		get_path(prg, env);
		find_npath(prg);
		cmd_access(prg, start);
	}
	execve(prg->av_execve[start], prg->av_execve, env);
	error_nl(prg, prg->av_execve[start]);
}

/* SIGINT - CONTROL C */
/* SIGQUIT - CONTROL \ */

/* Fork a process that executes the command */
/* As "execve" ends the calling process when successful, */
/* forking is necessary */
/* Do child will be divided into 3 processes */
/* 1. first_process- read from std out */
/* dprintf(2, "first process\n") */

void	execute_first_cmd(t_prg *prg, int *fd1, char **envp, int start)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		error_nl(prg, "Fork process");
	if (pid == 0)
	{
		dup2(fd1[1], STDOUT_FILENO);
		run_process(prg, envp, start);
	}
	else
		waitpid(pid, NULL, 0);
}

void	execute_middle_cmd(t_prg *prg, int *fd1, int *fd2, char **envp, int start)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		error_nl(prg, "Fork process");
	if (pid == 0)
	{
		dup2(fd1[0], STDIN_FILENO);
		dup2(fd2[1], STDOUT_FILENO);
		close(fd1[0]);
		close(fd1[1]);
		close(fd2[1]);
		run_process(prg, envp, start);
	}
	else
		waitpid(pid, NULL, 0);
}

void	execute_last_cmd(t_prg *prg, int *fd1, int *fd2, char **envp, int start)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		error_nl(prg, "Fork process");
	if (pid == 0)
	{
		if (prg->no_pipes == 1)
		{
			dup2(fd1[0], STDIN_FILENO);
			run_process(prg, envp, start);
		}
		else
		{
			dup2(fd2[0], STDIN_FILENO);
			close(fd2[0]);
			run_process(prg, envp, start);
		}
	}
	else
		waitpid(pid, NULL, 0);
}
