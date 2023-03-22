/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirection2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:48:23 by plau              #+#    #+#             */
/*   Updated: 2023/03/22 14:02:23 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Examples of < */
/* cat < file.txt */
/* sort < file.txt */
/* grep 'error' < $(ls *.log) */
int	ft_execute_redirection_output(char **envp, t_prg *prg, int i, char **av)
{
	int		j;
	int		k;
	char	*av_zero;

	j = 0;
	k = 0;
	av_zero = NULL;
	if ((ft_strncmp(av[0], "/", 1) != 0))
	{
		get_path(prg, envp);
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
	execve(av_zero, prg->av_execve, envp);
	error_nl(prg, "Redirection_output");
	return (1);
}

void	execute_command_output(t_prg *prg, char **envp, int outfile, int i, char **av)
{
	if (fork() == 0)
	{
		if (ft_execute_redirection_output(envp, prg, i, av))
			return ;
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
void	redirect_output(t_prg *prg, int i, char **envp, char **av)
{
	int	outfile;

	outfile = open(prg->all_token[i], O_RDONLY, 0644);
	if (outfile == -1)
		error_nl(prg, "unable to open file");
	execute_command_output(prg, envp, outfile, i, av);
}
