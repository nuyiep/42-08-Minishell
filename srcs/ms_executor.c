/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:33:39 by plau              #+#    #+#             */
/*   Updated: 2023/03/22 15:52:35 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Check cmd access */
char	*cmd_access(t_prg *prg, char *av_zero)
{
	int		j;
	char	*temp;

	j = 0;
	while (j < prg->npath)
	{
		temp = ft_strjoin(prg->path[j], "/");
		if (prg->no_pipes == 0)
			temp = ft_strjoin(temp, prg->all_token[0]);
		else
			temp = ft_strjoin(temp, av_zero);
		if (access(temp, X_OK) == 0)
		{
			if (prg->no_pipes == 0)
			{
				prg->all_token[0] = temp;
				return (prg->all_token[0]);
			}
			else
			{
				av_zero = temp;
				return (av_zero);
			}
		}
		j++;
		free(temp);
	}
	if (prg->no_pipes == 0)
		error_nl(prg, prg->all_token[0]);
	else
		error_nl(prg, av_zero);
	return (NULL);
}

/* dup2(temp_fd, 0) - redirects the stdin of the current process */
/*						to temp_fd */
/* fd[0]- read */
/* fd[1]- write */
/* Check if the input is a path address */
/* If it is not, change to address */
int	ft_execute(int temp_fd, char **envp, t_prg *prg)
{
	char	*empty_str;

	empty_str = ft_strdup("");
	dup2(temp_fd, 0);
	close(temp_fd);
	if ((ft_strncmp(prg->all_token[0], "/", 1) != 0))
		cmd_access(prg, empty_str);
	free(empty_str);
	execve(prg->all_token[0], prg->all_token, envp);
	error_nl(prg, prg->all_token[0]);
	return (1);
}

/* Just to execute one command */
int	single_command(t_prg *prg, char **envp)
{
	int	temp_fd;
	
	temp_fd = dup(0);
	if (fork() == 0)
	{
		if (ft_execute(temp_fd, envp, prg))
			return (2);
	}
	else
	{
		close(temp_fd);
		while (waitpid(-1, NULL, 0) != -1)
			;
		temp_fd = dup(0);
	}
	return (0);
}

/* Main function for executor */
/* If only one command, just execute using ft_execute */
/* Else, do_pipex */
/* temp_fd = dup(0) - Save stdin 0 to temp_fd */
/* fd[2] - create an empty fd[0] and fd[1] */
int	executor(t_prg *prg, char **envp)
{
	if (prg->no_pipes == 0)
	{
		single_command(prg, envp);
		return (1);
	}
	do_pipex(prg, envp);
	return (0);
}
