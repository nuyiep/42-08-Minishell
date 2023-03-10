/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:30:56 by plau              #+#    #+#             */
/*   Updated: 2023/03/10 21:53:31 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_many(t_prg *prg, int temp_fd, char **envp)
{
	dup2(temp_fd, 0);
	close(temp_fd);
	printf("token0= %s\n", prg->all_token[0]);
	if ((ft_strncmp(prg->all_token[0], "/", 1) != 0))
	{
		get_path(prg, envp);
		find_npath(prg);
		cmd_access(prg);
	}
	printf("token01= %s\n", prg->all_token[0]);
	execve(prg->all_token[0], prg->all_token, envp);
	return (1);
}

void	child_two(t_prg *prg, char **envp, int temp_fd)
{
	pid_t	pid;
	int		fd[2];

	pid = fork();
	if (pid == -1)
		error_nl(prg, "Fork failed");
	if (pid == 0)
	{
		dup2(temp_fd, STDOUT_FILENO);
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		printf("token2= %s\n", prg->all_token[2]);
		if ((ft_strncmp(prg->all_token[2], "/", 1) != 0))
		{
			get_path(prg, envp);
			find_npath(prg);
			cmd_access_two(prg);
		}
		printf("token21= %s\n", prg->all_token[2]);
		execve(prg->all_token[2], prg->all_token, envp);
	}
}

void	create_child(t_prg *prg, char **envp)
{
	pid_t	pid;
	int		fd[2];
	int		temp_fd;
	
	temp_fd = dup(0);
	if (pipe(fd) == -1)
		error_nl(prg, "Pipe failed");
	pid = fork();
	if (pid == -1)
		error_nl(prg, "Fork failed");
	if (pid == 0)
	{
		dup2(temp_fd, STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		if (ft_execute_many(prg, temp_fd, envp))
			error_nl(prg, "Failed to execute") ;
	}
	child_two(prg, envp, temp_fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
}

/* Create pipes for each pair of commands */
void	do_pipex(t_prg *prg, char **envp)
{
	create_child(prg, envp);
}
