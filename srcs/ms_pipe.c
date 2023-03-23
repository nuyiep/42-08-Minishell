/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:30:56 by plau              #+#    #+#             */
/*   Updated: 2023/03/22 21:52:17 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**make_pipes(t_prg *prg)
{
	int	i;
	int	**fd;

	i = 0;
	fd = malloc((prg->no_pipes) * sizeof(int *));
	while (i < prg->no_pipes)
	{
		fd[i] = malloc(2 * sizeof(int));
		pipe(fd[i]);
		i++;
	}
	return (fd);
}

void	one_pipe(t_prg *prg, char **split, int **fd, int no_cmds)
{
	char	**av_one;
	char	**av_last;
	int		i;

	av_one = NULL;
	av_last = NULL;
	i = 0;
	av_one = ft_split(split[0], ' ');
	execute_first_cmd(prg, fd, av_one, i);
	prg->av_execve = NULL;
	av_last = ft_split(split[no_cmds - 1], ' ');
	execute_last_cmd(prg, fd, av_last, i + 1);
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
	ft_freesplit(av_one);
	ft_freesplit(av_last);
	ft_freesplit(split);
	free(fd[0]);
	free(fd);
}

void	multiple_pipes(t_prg *prg, int **fd, int no_cmds, char **split)
{
	char	**av_one;
	char	**av_middle;
	char	**av_last;
	int		i;

	i = 0;
	av_one = ft_split(split[0], ' ');
	execute_first_cmd(prg, fd, av_one, i);
	prg->av_execve = NULL;
	i++;
	while (i < no_cmds - 1)
	{
		av_middle = ft_split(split[i], ' ');
		execute_middle_cmd(prg, fd, av_middle, i);
		prg->av_execve = NULL;
		ft_freesplit(av_middle);
		i++;
	}
	av_last = ft_split(split[no_cmds - 1], ' ');
	execute_last_cmd(prg, fd, av_last, i);
	ft_freesplit(av_one);
	ft_freesplit(av_last);
}

void	wait_free(int no_cmds, t_prg *prg, int **fd)
{
	int	i;

	i = 0;
	while (i < no_cmds)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	i = 0;
	while (i < prg->no_pipes)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}

/* Create pipes for each pair of commands */
/* then calls fork for each command given */
/* Examples */
/* ls | ls | ls  */
/* ls | wc -l */
/* cat file.txt | wc -l */
/* cat file.txt | grep "world" | wc -l */
/* cat | cat | ls */
/* If have 2 commands, need 2 child processes, but only 1 pipe */
void	do_pipex(t_prg *prg)
{
	char	**split;
	int		no_cmds;
	int		i;
	int		**fd;

	no_cmds = 0;
	fd = make_pipes(prg);
	split = ft_split(prg->input, '|');
	i = 0;
	while (split[no_cmds] != NULL)
		no_cmds++;
	if (prg->no_pipes == 1)
	{
		one_pipe(prg, split, fd, no_cmds);
		return ;
	}
	else
		multiple_pipes(prg, fd, no_cmds, split);
	ft_freesplit(split);
	wait_free(no_cmds, prg, fd);
}
