/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:33:39 by plau              #+#    #+#             */
/*   Updated: 2023/03/09 12:15:37 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* dup2(temp_fd, 0) - redirects the stdin of the current process */
/*						to temp_fd */
/* fd[0]- read */
/* fd[1]- write */
int	ft_execute(char **av, int i, int temp_fd, char **envp, t_prg *prg)
{
	av[i] = NULL;
	dup2(temp_fd, 0);
	close(temp_fd);
	execve(av[0], av, envp);
	error_nl(prg, av[0]);
	return (1);
}

/* Main function for executor */
/* temp_fd = dup(0) - Save stdin 0 to temp_fd */
/* fd[2] - create an empty fd[0] and fd[1] */
int	executor(t_prg *prg, char **av, char **envp)
{
	if (prg->all_token[0] == NULL)
		return (3);
	if (ms_heredoc(prg, av, envp) == 0)
		return (2);
	int	i;
	int	temp_fd;
	int	fd[2];

	i = 0;
	temp_fd = dup(0);
	while (av[i] && av[i + 1])
	{
		av = &av[i + 1];
		i = 0;
		while (av[i] && ft_strcmp(av[i], ";") && ft_strcmp(av[i], "|"))
			i++;
		if (i != 0 && (av[i] == NULL || ft_strcmp(av[i], ";") == 0))
		{
			if (fork() == 0)
			{
				if (ft_execute(av, i, temp_fd, envp, prg))
					return (1);
			}
			else
			{
				close(temp_fd);
				while (waitpid(-1, NULL, 0) != -1)
					;
				temp_fd = dup(0);
			}
		}
		else if (i != 0 && ft_strcmp(av[i], "|"))
		{
			pipe(fd);
			if (fork() == 0)
			{
				dup2(fd[1], 1);
				close(fd[0]);
				close(fd[1]);
				if (ft_execute(av, i, temp_fd, envp, prg))
					return (1);
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
}
