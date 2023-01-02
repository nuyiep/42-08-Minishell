/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 17:29:48 by plau              #+#    #+#             */
/*   Updated: 2022/12/31 13:07:11 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Check whether can open input and output file  */
void	check_open(t_prg *prg)
{
	prg->fd_in = open(prg->token.infile, O_RDONLY);
	if (prg->fd_in == -1)
		error_nl(prg, "Invalid infile");
}

/* Create a child process so that it can execute command more than once */
void	create_child(t_prg *prg)
{
	pid_t	pid;
	int		i;

	i = 0;
	while (i < prg->ccmd)
	{
		if (pipe(prg->fd) == -1)
			error_nl(prg, "Pipe failed");
		pid = fork();
		if (pid == -1)
			error_nl(prg, "Fork failed");
		if (pid == 0)
		{
			dup2(prg->fd_in, STDIN_FILENO);
			dup2(prg->fd[1], STDOUT_FILENO);
			close(prg->fd[0]);
			execve(prg->cmdpath1, prg->token.all_cmd1, prg->ls_envp);
		}
		close(prg->fd[1]);
		waitpid(-1, NULL, 0);
		i++;
	}
}
