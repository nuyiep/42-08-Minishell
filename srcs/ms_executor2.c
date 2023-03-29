/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:49:57 by plau              #+#    #+#             */
/*   Updated: 2023/03/29 17:50:10 by plau             ###   ########.fr       */
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
		single_command(prg);
		return (1);
	}
	do_pipex(prg);
	return (0);
}
