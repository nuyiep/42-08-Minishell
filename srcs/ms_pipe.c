/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:30:56 by plau              #+#    #+#             */
/*   Updated: 2023/03/16 10:17:42 by plau             ###   ########.fr       */
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

/* Creates a pipe for each pair of commands */
int	**make_pipes(t_prg *prg)
{
	int	i;
	int	**fd;

	i = 0;
	fd = malloc((prg->no_pipes + 2) * sizeof(int *));
	while (i <= prg->no_pipes)
	{
		fd[i] = malloc(2 * sizeof(int));
		pipe(fd[i]);
		i++;
	}
	fd[prg->no_pipes + 1] = NULL;
	return (fd);
}

/* Create pipes for each pair of commands */
/* then calls fork for each command given */
void	do_pipex(t_prg *prg, char **envp)
{
	int	no_tokens;
	int	no_cmds;
	int	**fd;
	int	i;

	no_tokens = 0;
	fd = make_pipes(prg);
	while (prg->all_token[no_tokens] != NULL)
		no_tokens++;
	no_cmds = no_tokens - prg->no_pipes;
	i = 0;
	while (i < no_cmds)
	{
		fork_process(prg, envp, fd, i);
		i++;
	}
	fork_last_process(prg, envp, i);
	i = 0;
	while (i < (prg->no_pipes + 2))
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}
