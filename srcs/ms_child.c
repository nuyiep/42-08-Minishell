/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:02:02 by plau              #+#    #+#             */
/*   Updated: 2023/03/14 13:16:58 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Get input from stdin put into fd[0][1] - write end */
/* Get input from fd[0][1] to fd[0][0] */
/* STDIN -> fd[0][1] -> fd[0][0] */
/* close fd[0][1] */
void	dup_first_process(int **fd)
{
	dup2(fd[0][1], STDIN);
	dup2(fd[0][0], fd[0][1]);
	printf("dup first process\n");
	close(fd[0][1]);
}

/* For second pipe */
void	dup_middle_process(int **fd, int i)
{
	dup2(fd[i][1], fd[i - 1][0]);
	dup2(fd[i][0], fd[i][1]);
	printf("dup middle proces\n");
	close(fd[0][0]);
	close(fd[i][1]);
}

void	dup_last_process(int **fd, int i)
{
	dup2(fd[i][1], fd[i - 1][0]);
	dup2(STDOUT, fd[i][1]);
	printf("dup last process\n");
	close(fd[i - 1][0]);
	close(fd[i][1]);
}

/* Finds the PATH where the command is located */
/* and executes it. Process ends when execve is successful */
void	run_process(int i, t_prg *prg, char **env)
{
	// to open later on and replace token
	// if ((ft_strncmp(prg->all_token[i], "/", 1) != 0))
	// {
	// 	get_path(prg, env);
	// 	find_npath(prg);
	// 	cmd_access(prg);
	// }
	char	**av = NULL;
	if (i == 0)
		av[i] = "/bin/ls";
	else if (i == 1) // token[2] ls | ls 
		av[i] = "/bin/ls";
	else if (i == 2) //token [3] ls | ls | ls
		av[i] = "/bin/ls";
	printf("run process\n");
	execve("ls", av, env);
	error_nl(prg, prg->all_token[0]);
}

/* SIGINT - CONTROL C */
/* SIGQUIT - CONTROL \ */

/* Fork a process that executes the command */
/* As "execve" ends the calling process when successful, */
/* forking is necessary */
/* Do child will be divided into 3 processes */
/* 1. first_process- read from std out */

void	fork_process(t_prg *prg, char **envp, int **fd, int i, int no_cmds)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		error_nl(prg, "Fork process");
	if (pid == 0)
	{
		if (i == 0)
		{
			dup_first_process(fd);
			run_process(i, prg, envp);
		}
		else if (i == no_cmds)
		{
			printf("no_cmds: %d\n", no_cmds);
			dup_last_process(fd, i);
		}
		else
			dup_middle_process(fd, i);
		run_process(i, prg, envp);
	}
	else
		waitpid(pid, NULL, 0);
}
