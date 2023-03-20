/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:30:56 by plau              #+#    #+#             */
/*   Updated: 2023/03/20 16:02:26 by plau             ###   ########.fr       */
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
	int		no_cmds;
	char	**av_one;
	char	**av_last;
	char	**av_middle;
	int		i;

	end = 0;
	start = 0;
	count_pipes = 0;
	pipe(fd1);
	pipe(fd2);
	no_cmds = 0;
	
	split = ft_split(prg->input, '|');
	av_one = NULL;
	av_last = NULL;
	av_middle = NULL;
	i = 1;
	while (split[no_cmds] != NULL)
		no_cmds++;
	if (prg->no_pipes == 1)
	{
		av_one = ft_split(split[0], ' ');
		execute_first_cmd(prg, fd1, envp, start, av_one);
	}
	else
	{
		av_one = ft_split(split[0], ' ');
		execute_first_cmd(prg, fd1, envp, start, av_one);
		while (i < no_cmds - 1)
		{
			av_middle = ft_split(split[i], ' ');
			if (i % 2 != 0)
				execute_middle_cmd_odd(prg, fd1, fd2, envp, start, av_middle);
			else
				execute_middle_cmd_even(prg, fd1, fd2, envp, start, av_middle);
			free(av_middle);
			i++;
		}
	}
	av_last = ft_split(split[no_cmds - 1], ' ');
	execute_last_cmd(prg, fd1, fd2, envp, start, av_last);
	ft_freesplit(av_one);
	ft_freesplit(av_last);
	ft_freesplit(split);
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
	i = 0;
	while (i < no_cmds - 2 && no_cmds > 2)
	{
		waitpid(-1, NULL, 0);
		i++;
	}	
}
