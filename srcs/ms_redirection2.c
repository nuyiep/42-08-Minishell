/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirection2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:48:23 by plau              #+#    #+#             */
/*   Updated: 2023/03/18 13:08:18 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Examples of < */
/* cat < file.txt */
/* sort < file.txt */
/* grep 'error' < $(ls *.log) */
int	ft_execute_redirection_output(char **envp, t_prg *prg, int i)
{
	int	j;
	int	k;
	int	start;

	j = 0;
	k = 0;
	start = 0;
	if ((ft_strncmp(prg->all_token[0], "/", 1) != 0))
	{
		get_path(prg, envp);
		find_npath(prg);
		cmd_access(prg, start);
	}
	prg->av_execve = prg->all_token;
	while (prg->all_token[k] != NULL)
	{
		if (k == i - 1)
			k++;
		prg->av_execve[j] = prg->all_token[k];
		j++;
		k++;
	}
	prg->av_execve[j] = NULL;
	execve(prg->all_token[0], prg->av_execve, envp);
	error_nl(prg, "Redirection_output");
	return (1);
}

void	execute_command_output(t_prg *prg, char **envp, int outfile, int i)
{
	if (fork() == 0)
	{
		if (ft_execute_redirection_output(envp, prg, i))
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
void	redirect_output(t_prg *prg, int i, char **envp)
{
	int	outfile;

	outfile = open(prg->all_token[i], O_RDONLY, 0644);
	if (outfile == -1)
		error_nl(prg, "unable to open file");
	execute_command_output(prg, envp, outfile, i);
}
