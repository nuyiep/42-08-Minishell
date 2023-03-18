/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:02:02 by plau              #+#    #+#             */
/*   Updated: 2023/03/17 19:26:02 by plau             ###   ########.fr       */
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

void	fork_process(t_prg *prg, char **envp, int *fd, int start, int count_pipes)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		error_nl(prg, "Fork process");
	if (pid == 0)
	{
		if (count_pipes == 0)
		{
			dup2(fd[1], STDOUT_FILENO);
		}
		else if (count_pipes == prg->no_pipes - 1)
		{
			dup2(fd[0], STDIN_FILENO);
		}
		else
		{
			dup2(fd[1], STDOUT_FILENO);
			dup2(fd[0], STDIN_FILENO);
		}
		close(fd[0]);
		close(fd[1]);
		run_process(prg, envp, start);
	}
	else
		waitpid(pid, NULL, 0);
	(void)count_pipes;
}
