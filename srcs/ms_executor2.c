/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:49:57 by plau              #+#    #+#             */
/*   Updated: 2023/03/30 21:32:38 by nchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Main function for executor */
/* If only one command, just execute using ft_execute */
/* Else, do_pipex */
/* temp_fd = dup(0) - Save stdin 0 to temp_fd */
/* fd[2] - create an empty fd[0] and fd[1] */
int	executor(t_prg *prg)
{
	if (prg->no_pipes == 0)
	{
		if (!check_syntax(prg->all_token))
			return (1);
		single_command(prg);
		return (1);
	}
	do_pipex(prg);
	return (0);
}

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
