/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:02:02 by plau              #+#    #+#             */
/*   Updated: 2023/03/30 15:57:21 by nchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Close pipes for each child process */
void	close_pipes(int **fd)
{
	int	i;

	i = -1;
	while (fd[++i])
	{
		close(fd[i][0]);
		close(fd[i][1]);
		free(fd[i]);
	}
	free(fd);
}

/* Close pipes for all parent process only at the end */
void	close_last(int **fd)
{
	int	i;

	i = -1;
	while (fd[++i])
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
}

/* Finds the PATH where the command is located */
/* and executes it. Process ends when execve is successful */
/* Example: ls | ls | ls or  */
void	run_process(t_prg *prg, char **av)
{
	if ((ft_strncmp(av[0], "/", 1) != 0))
	{
		get_path(prg, prg->ls_envp);
		find_npath(prg);
		av[0] = cmd_access(prg, av[0]);
	}
	execve(av[0], av, prg->ls_envp);
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
/* first cmd - [unclosed] child will write [1] */
/* 			 - child read end need to close [0] */
/* 			 - parent write end need to close */
/*			 - [unclosed] parent read end - remain unclosed - for the next */
/*				cmd to read from */
void	execute_first_cmd(t_prg *prg, int **fd, char **av_one, int i)
{
	int	pid;
	int	status;

	if (!check_syntax(av_one))
		return ;
	if (check_redirection_builtins(prg, av_one) == 1)
		return ;
	pid = fork();
	if (pid < 0)
		error_nl(prg, "Fork process");
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(fd[i][1], STDOUT_FILENO);
		close_pipes(fd);
		run_process(prg, av_one);
	}
	else
		waitpid(0, &status, -1);
}

void	execute_middle_cmd(t_prg *prg, int **fd, char **av_middle, int i)
{
	int	pid;
	int	status;
	
	if (!check_syntax(av_middle))
		return ;
	if (check_redirection_builtins(prg, av_middle) == 1)
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
		close_pipes(fd);
		run_process(prg, av_middle);
	}
	else
		waitpid(0, &status, -1);
}

void	execute_last_cmd(t_prg *prg, int **fd, char **av_last, int i)
{
	int		pid;
	int		status;

	if (!check_syntax(av_last))
		return ;
	if (check_redirection_builtins(prg, av_last) == 1)
		return ;
	pid = fork();
	if (pid < 0)
		error_nl(prg, "Fork process");
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(fd[i - 1][0], STDIN_FILENO);
		close_pipes(fd);
		run_process(prg, av_last);
	}
	else
	{
		waitpid(0, &status, -1);
		close_last(fd);
	}
}
