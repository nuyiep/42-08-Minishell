/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:33:39 by plau              #+#    #+#             */
/*   Updated: 2023/03/10 19:04:02 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* To get the "PATH=" line from env */
void	get_path(t_prg *prg, char **envp)
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_substr(envp[i], 5, (ft_strlen(envp[i]) - 5));
			prg->path = ft_split(path, ':');
			free (path);
		}
		i++;
	}
}

/* Find number of path */
void	find_npath(t_prg *prg)
{
	int	k;

	k = 0;
	while (prg->path[k] != NULL)
		k++;
	prg->npath = k;
}

/* Check cmd access */
void	cmd_access(t_prg *prg)
{
	int		j;
	char	*temp;

	j = 0;
	while (j < prg->npath)
	{
		temp = ft_strjoin(prg->path[j], "/");
		temp = ft_strjoin(temp, prg->all_token[0]);
		if (access(temp, F_OK) == 0)
		{
			prg->all_token[0] = temp;
			// free(temp);
			return ;
		}
		j++;
		free(temp);
	}
	error_nl(prg, "Invalid command");
}

/* dup2(temp_fd, 0) - redirects the stdin of the current process */
/*						to temp_fd */
/* fd[0]- read */
/* fd[1]- write */
/* Check if the input is a path address */
/* If it is not, change to address */
int	ft_execute(int i, int temp_fd, char **envp, t_prg *prg)
{
	dup2(temp_fd, 0);
	close(temp_fd);
	if ((ft_strncmp(prg->all_token[0], "/", 1) != 0))
	{
		get_path(prg, envp);
		find_npath(prg);
		cmd_access(prg);
	}
	execve(prg->all_token[0], prg->all_token, envp);
	error_nl(prg, prg->all_token[0]);
	return (1);
	(void)i;
}

/* Main function for executor */
/* temp_fd = dup(0) - Save stdin 0 to temp_fd */
/* fd[2] - create an empty fd[0] and fd[1] */
int	executor(t_prg *prg, char **av, char **envp)
{
	int	i;
	int	temp_fd;

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
	do_pipex(prg, envp);
	(void)av;
	return (0);
}
