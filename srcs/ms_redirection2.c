/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirection2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:48:23 by plau              #+#    #+#             */
/*   Updated: 2023/03/29 17:18:56 by plau             ###   ########.fr       */
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
		prg->av_execve[j++] = av[k++];
	}
	prg->av_execve[j] = NULL;
	execve(av_zero, prg->av_execve, prg->ls_envp);
	error_nl(prg, av_zero);
	return (1);
}

/* cat < Makefile */
/* Only print out the last command, the rest store in pipe */
int	redirect_output(t_prg *prg, int i, char **av, int **fd)
{
	int	outfile;
	int	status;

	outfile = open(av[i], O_RDONLY, 0644);
	if (fork() == 0)
	{
		if (outfile == -1)
		{
			exit_code = 1;
			error_nl(prg, prg->all_token[i]);
		}
		if (prg->cmd_pos != prg->no_pipes)
		{
			dup2(fd[prg->cmd_pos][1], STDOUT_FILENO);
			close_pipes(fd);
			if (ft_execute_redirection_output(prg, i, av))
				error_nl(prg, "Redirection_output");
		}
		else
		{
			if (ft_execute_redirection_output(prg, i, av))
				error_nl(prg, "Redirection_output");
		}
	}
	else
	{
		close(outfile);
		waitpid(-1, &status, WUNTRACED);
		if (WIFEXITED(status))
			exit_code = (WEXITSTATUS(status));
	}
	return (1);
}
