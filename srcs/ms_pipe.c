/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:30:56 by plau              #+#    #+#             */
/*   Updated: 2023/03/31 17:07:06 by nchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_free(int no_cmds, t_prg *prg, int **fd);

int	**make_pipes(t_prg *prg)
{
	int	i;
	int	**fd;

	i = 0;
	fd = malloc((prg->no_pipes + 1) * sizeof(int *));
	while (i < prg->no_pipes)
	{
		fd[i] = malloc(2 * sizeof(int));
		pipe(fd[i]);
		i++;
	}
	fd[i] = NULL;
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
	prg->cmd_pos = i;
	av_one = ft_split(split[0], ' ');
	execute_first_cmd(prg, fd, av_one, prg->cmd_pos);
	prg->av_execve = NULL;
	av_last = ft_split(split[no_cmds - 1], ' ');
	execute_last_cmd(prg, fd, av_last, prg->cmd_pos + 1);
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
	ft_freesplit(av_one);
	ft_freesplit(av_last);
	ft_freesplit(split);
	wait_free(2,prg, fd);
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
		waitpid(-1, NULL, WUNTRACED);
		i++;
	}
	i = 0;
	while (fd[i])
	{
		free(fd[i]);
		i++;
	}
	(void)prg;
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
	int		**fd;

	no_cmds = 0;
	fd = make_pipes(prg);
	split = get_cmd(prg);
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
