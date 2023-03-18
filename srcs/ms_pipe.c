/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:30:56 by plau              #+#    #+#             */
/*   Updated: 2023/03/18 17:27:17 by plau             ###   ########.fr       */
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
/* If have 2 commands, need 2 child processes, but only 1 pipe */
void	do_pipex(t_prg *prg, char **envp)
{
	int		end;
	int		start;
	int		count_pipes;
	int		fd1[2];
	int		fd2[2];
	char	**split;
	int		i;
	char	**av_one;
	char	**av_two;

	end = 0;
	start = 0;
	count_pipes = 0;
	pipe(fd1);
	pipe(fd2);
	i = 0;
	
	split = ft_split(prg->input, '|');
	if (prg->no_pipes == 1)
	{
		av_one = ft_split(split[0], ' ');
		execute_first_cmd(prg, fd1, envp, start, av_one);
		av_two = ft_split(split[1], ' ');
		execute_last_cmd(prg, fd1, fd2, envp, start, av_two);
	}
}
