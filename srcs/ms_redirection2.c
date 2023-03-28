/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirection2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:48:23 by plau              #+#    #+#             */
/*   Updated: 2023/03/28 15:43:36 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Examples of < */
/* cat < file.txt */
/* sort < file.txt */
/* grep 'error' < $(ls *.log) */
int	ft_execute_redirection_output(t_prg *prg, int i, char **av)
{
	int		j;
	int		k;
	char	*av_zero;

	j = 0;
	k = 0;
	av_zero = NULL;
	if ((ft_strncmp(av[0], "/", 1) != 0))
	{
		get_path(prg, prg->ls_envp);
		find_npath(prg);
		av_zero = cmd_access(prg, av[0]);
	}
	prg->av_execve = av;
	while (av[k] != NULL)
	{
		if (k == i - 1)
			k++;
		prg->av_execve[j] = av[k];
		j++;
		k++;
	}
	prg->av_execve[j] = NULL;
	execve(av_zero, prg->av_execve, prg->ls_envp);
	return (1);
}

void	execute_command_output(t_prg *prg, int outfile, int i, char **av)
{
	if (fork() == 0)
	{
		if (ft_execute_redirection_output(prg, i, av))
			error_nl(prg, "Redirection_output");
	}
	else
	{
		close(outfile);
		while (waitpid(-1, NULL, 0) != -1)
			;
	}
	return ;
}

/* cat < Makefile */
int	redirect_output(t_prg *prg, int i, char **av)
{
	int	outfile;

	outfile = open(prg->all_token[i], O_RDONLY, 0644);
	if (outfile == -1)
	{
		exit_code = 2;
		error_nl(prg, "unable to open file");
	}
	execute_command_output(prg, outfile, i, av);
	return (1);
}
