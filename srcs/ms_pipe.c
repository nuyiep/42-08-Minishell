/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:30:56 by plau              #+#    #+#             */
/*   Updated: 2023/03/21 12:18:46 by plau             ###   ########.fr       */
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

/* Create pipes for each pair of commands */
/* then calls fork for each command given */
/* Examples */
/* ls | ls | ls  */
/* ls | wc -l */
/* cat file.txt | wc -l */
/* cat file.txt | grep "world" | wc -l */
/* cat | cat | ls */
/* If have 2 commands, need 2 child processes, but only 1 pipe */
void	do_pipex(t_prg *prg, char **envp)
{
	char	**split;
	int		no_cmds;
	char	**av_one;
	char	**av_middle;
	char	**av_last;
	int		i;
	int		**fd;

	no_cmds = 0;
	fd = make_pipes(prg);
	split = ft_split(prg->input, '|');
	av_one = NULL;
	av_last = NULL;
	av_middle = NULL;
	i = 0;
	while (split[no_cmds] != NULL)
		no_cmds++;
	if (prg->no_pipes == 1)
	{
		av_one = ft_split(split[0], ' ');
		execute_first_cmd(prg, fd, envp, av_one, i);
		av_last = ft_split(split[no_cmds - 1], ' ');
		execute_last_cmd(prg, fd, envp, av_last, i + 1);
	}
	else
	{
		av_one = ft_split(split[0], ' ');
		execute_first_cmd(prg, fd, envp, av_one, i);
		i++;
		while (i < no_cmds - 1)
		{
			av_middle = ft_split(split[i], ' ');
			execute_middle_cmd(prg, fd, envp, av_middle, i);
			free(av_middle);
			i++;
		}
		av_last = ft_split(split[no_cmds - 1], ' ');
		execute_last_cmd(prg, fd, envp, av_last, i);
	}
	i = 0;
	while (i < no_cmds)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	ft_freesplit(av_one);
	ft_freesplit(av_last);
	ft_freesplit(split);
}
