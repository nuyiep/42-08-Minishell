/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:33:39 by plau              #+#    #+#             */
/*   Updated: 2023/03/09 15:21:11 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* dup2(temp_fd, 0) - redirects the stdin of the current process */
/*						to temp_fd */
/* fd[0]- read */
/* fd[1]- write */
int	ft_execute(int i, int temp_fd, char **envp, t_prg *prg)
{
	if (prg->all_token[1] != NULL)
		prg->all_token[i] = NULL;
	dup2(temp_fd, 0);
	close(temp_fd);
	execve(prg->all_token[0], prg->all_token, envp);
	error_nl(prg, prg->all_token[0]);
	return (1);
}

/* Main function for executor */
/* temp_fd = dup(0) - Save stdin 0 to temp_fd */
/* fd[2] - create an empty fd[0] and fd[1] */
int	executor(t_prg *prg, char **av, char **envp)
{
	int	i;
	int	temp_fd;
	int	fd[2];

	i = 0;
	temp_fd = dup(0);
	if (prg->all_token[1] == NULL)
	{
		if (fork() == 0)
		{
			if (ft_execute(i, temp_fd, envp, prg))
				return (0);
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
	while (prg->all_token[i] && prg->all_token[i + 1])
	{
		prg->all_token = &prg->all_token[i + 1];
		i = 0;
		while (prg->all_token[i] && ft_strcmp(prg->all_token[i], ";") && ft_strcmp(prg->all_token[i], "|"))
			i++;
		if (i != 0 && (prg->all_token[i] == NULL || ft_strcmp(prg->all_token[i], ";") == 0))
		{
			if (fork() == 0)
			{
				if (builtins(prg, envp))
					return (0);
				if (ft_execute(i, temp_fd, envp, prg))
					return (0);
			}
			else
			{
				close(temp_fd);
				while (waitpid(-1, NULL, 0) != -1)
					;
				temp_fd = dup(0);
			}
		}
		else if (i != 0 && ft_strcmp(prg->all_token[i], "|"))
		{
			pipe(fd);
			if (fork() == 0)
			{
				dup2(fd[1], 1);
				close(fd[0]);
				close(fd[1]);
				if (builtins(prg, envp))
					return (0);
				if (ft_execute(i, temp_fd, envp, prg))
					return (0);
			}
			else
			{
				close(fd[1]);
				close(temp_fd);
				temp_fd = fd[0];			
			}
		}
	}
	close(temp_fd);
	return (0);
	(void)av;
}
