/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:30:56 by plau              #+#    #+#             */
/*   Updated: 2023/03/14 16:24:36 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_access(t_prg *prg, char *token_path)
{
	if (access(token_path, X_OK) == 0)
		return ;
	else
		error_nl(prg, "Command is invalid");
}

int	count_pipe(t_prg *prg)
{
	int	i;
	int	no_pipe;

	i = 0;
	no_pipe = 0;
	while (prg->all_token[i] != NULL)
	{
		if (ft_strcmp(prg->all_token[i], "|") == 0)
			no_pipe++;
		i++;
	}
	return (no_pipe);
}

/* Creates a pipe for each pair of commands */
int	**make_pipes(t_prg *prg, int no_pipes)
{
	int	i;
	int	**fd;

	i = 0;
	fd = malloc((no_pipes + 2) * sizeof(int *));
	while (i <= no_pipes)
	{
		fd[i] = malloc(2 * sizeof(int));
		pipe(fd[i]);
		i++;
	}
	fd[no_pipes + 1] = NULL;
	return (fd);
	(void)prg;
}

void	close_pipes(int **fd)
{
	int	i;

	i = 0;
	while (fd[i])
	{
		close(fd[i][0]);
		close(fd[i][1]);
		free(fd[i]);
		i++;
	}
}

/* Create pipes for each pair of commands */
/* then calls fork for each command given */
void	do_pipex(t_prg *prg, char **envp)
{
	int	no_tokens;
	int	no_pipes;
	int	no_cmds;
	int	**fd;
	int	i;

	no_tokens = 0;
	no_pipes = count_pipe(prg);
	fd = make_pipes(prg, no_pipes);
	while (prg->all_token[no_tokens] != NULL)
		no_tokens++;
	no_cmds = no_tokens - no_pipes;
	i = 0;
	while (i <= no_cmds)
	{
		// if (i == 0)
		// {
		// 	fork_process(prg, envp, fd, i, no_cmds);
		// 	i++;
		// 	continue ;
		// }
		fork_process(prg, envp, fd, i, no_cmds);
		i++;
	}
	// printf("i = %d\n", i);
	// fork_process(prg, envp, fd, i, no_cmds);
}
