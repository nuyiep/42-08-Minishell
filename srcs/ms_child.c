/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:02:02 by plau              #+#    #+#             */
/*   Updated: 2023/03/14 19:45:39 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	fork_process(t_prg *prg, char **envp, int **fd, int i)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		error_nl(prg, "Fork process");
	if (pid == 0)
	{
		dup2(fd[i][0], STDIN_FILENO);
		dup2(fd[i + 1][1], STDOUT_FILENO);
		close(fd[i][0]);
		close(fd[i][1]);
		run_process(i, prg, envp);
	}
	else
		waitpid(pid, NULL, 0);
}

void	fork_last_process(t_prg *prg, char **envp, int i)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		error_nl(prg, "Fork last process");
	if (pid == 0)
	{
		run_process(i, prg, envp);
	}
	else
		waitpid(pid, NULL, 0);
}
