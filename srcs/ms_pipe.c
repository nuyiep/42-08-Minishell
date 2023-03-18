/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:30:56 by plau              #+#    #+#             */
/*   Updated: 2023/03/17 19:24:24 by plau             ###   ########.fr       */
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
/* Examples */
/* ls | ls | ls  */
/* ls | wc -l */
/* cat file.txt | wc -l */
/* cat file.txt | grep "world" | wc -l */
/* cat | cat | ls */
void	do_pipex(t_prg *prg, char **envp)
{
	int	fd[2];
	int	end;
	int	start;
	int	count_pipes;

	// fd = make_pipes(prg);
	end = 0;
	start = 0;
	count_pipes = 0;
	prg->av_execve = prg->all_token;
	while (prg->all_token[end] != NULL)
	{
		if (ft_strcmp(prg->all_token[end], "|") == 0)
		{
			prg->av_execve[end] = NULL;
			fork_process(prg, envp, fd, start, count_pipes);
			count_pipes++;
			start = end + 1;
		}
		if (prg->no_pipes == count_pipes)
			break ;
		end++;
	}
	fork_process(prg, envp, fd, start, count_pipes);
	// end = 0;
	// while (end < (prg->no_pipes + 2))
	// {
	// 	free(fd[end]);
	// 	end++;
	// }
	// free(fd);
}
