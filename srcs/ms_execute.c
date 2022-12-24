/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 17:29:48 by plau              #+#    #+#             */
/*   Updated: 2022/12/24 18:02:39 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Create a child process so that it can execute command more than once */
void	child_process(t_prg *prg, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit_error("Fork");
	if (pid == 0)
		execve(prg->cmdpath, prg->cmd, envp);
	else
		wait(NULL);
}
