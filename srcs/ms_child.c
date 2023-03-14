/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:02:02 by plau              #+#    #+#             */
/*   Updated: 2023/03/14 15:28:44 by plau             ###   ########.fr       */
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
	printf("first process\n");
	close(fd[0][1]);
}

/* For second pipe */
void	dup_middle_process(int **fd, int i)
{
	dup2(fd[i][1], fd[i - 1][0]);
	dup2(fd[i][0], fd[i][1]);
	printf("middle proces\n");
	close(fd[i - 1][0]);
	close(fd[i][1]);
}

void	dup_last_process(int **fd, int i)
{
	dup2(fd[i][1], fd[i - 1][0]);
	printf("last process\n");
	dup2(STDOUT, fd[i][1]);
	close(fd[i - 1][0]);
	close(fd[i][1]);
	close(fd[i][0]);
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
	char	*path = "/bin/ls";
	char	**split;
	char	*hard_code = "ls";

	split = ft_split(hard_code, ' ');
	execve(path, split, env);
	error_nl(prg, prg->all_token[0]);
	(void)i;
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
			printf("here\n");
			dup_last_process(fd, i);
		}
		else
		{
			dup_middle_process(fd, i);
			run_process(i, prg, envp);
		}
	}
	else
		waitpid(pid, NULL, 0);
}
