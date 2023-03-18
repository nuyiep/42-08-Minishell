/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:02:02 by plau              #+#    #+#             */
/*   Updated: 2023/03/18 19:30:15 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Finds the PATH where the command is located */
/* and executes it. Process ends when execve is successful */
/* Example: ls | ls | ls or  */
void	run_process(t_prg *prg, char **env, int start, char **av)
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
	(void)start;
}

/* SIGINT - CONTROL C */
/* SIGQUIT - CONTROL \ */

/* Fork a process that executes the command */
/* As "execve" ends the calling process when successful, */
/* forking is necessary */
/* Do child will be divided into 3 processes */
/* 1. first_process- read from std out */
/* dprintf(2, "first process\n") */

void	execute_first_cmd(t_prg *prg, int *fd1, char **envp, int start, char **av_one)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		error_nl(prg, "Fork process");
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(fd1[0]);
		dup2(fd1[1], STDOUT_FILENO);
		run_process(prg, envp, start, av_one);
	}
	else
		close(fd1[1]);
}

// void	execute_middle_cmd(t_prg *prg, int *fd1, int *fd2, char **envp, int start)
// {
// 	int	pid;

// 	pid = fork();
// 	if (pid < 0)
// 		error_nl(prg, "Fork process");
// 	if (pid == 0)
// 	{
// 		dup2(fd1[0], STDIN_FILENO);
// 		dup2(fd2[1], STDOUT_FILENO);
// 		close(fd1[0]);
// 		close(fd1[1]);
// 		close(fd2[1]);
// 		run_process(prg, envp, start);
// 	}
// 	else
// 		waitpid(pid, NULL, 0);
// }

void	execute_last_cmd(t_prg *prg, int *fd1, int *fd2, char **envp, int start, char **av_two)
{
	int		pid;

	pid = fork();
	if (pid < 0)
		error_nl(prg, "Fork process");
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (prg->no_pipes == 1)
		{
			dprintf(2, "close write: %d\n", close(fd1[1]));
			dup2(fd1[0], STDIN_FILENO);
			run_process(prg, envp, start, av_two);
		}
		// else
		// {
		// 	dup2(fd2[0], STDIN_FILENO);
		// 	close(fd2[0]);
		// 	run_process(prg, envp, start, av_two);
		// }
	}
	else
		close(fd1[0]);
	(void)fd2;
}
