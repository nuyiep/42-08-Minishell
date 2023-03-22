/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:49:30 by plau              #+#    #+#             */
/*   Updated: 2023/03/22 18:29:24 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Examples of >> append */
/* pwd >> file.txt */
/* date >> file.txt */
/* echo "Hello World" >> file.txt */
int	ft_execute_redirection(int infile, char **envp, t_prg *prg, char **av)
{
	char	*av_zero;

	av_zero = NULL;
	dup2(infile, STDOUT_FILENO);
	close(infile);
	if ((ft_strncmp(av[0], "/", 1) != 0))
		av_zero = cmd_access(prg, av[0]);
	execve(av_zero, prg->av_execve, envp);
	error_nl(prg, av_zero);
	return (1);
}

void	execute_single_command(t_prg *prg, char **envp, int file, char **av)
{
	if (fork() == 0)
	{
		if (ft_execute_redirection(file, envp, prg, av))
			return ;
	}
	else
	{
		close(file);
		while (waitpid(-1, NULL, 0) != -1)
			;
	}
	return ;
}

void	redirect_append(t_prg *prg, int i, char **envp, char **av)
{
	int	infile;

	infile = open(av[i], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (infile == -1)
		error_nl(prg, "unable to open file");
	prg->av_execve = NULL;
	prg->av_execve = av;
	free(prg->av_execve[i]);
	free(prg->av_execve[i - 1]);
	prg->av_execve[i - 1] = NULL;
	execute_single_command(prg, envp, infile, av);
}

/* ls > ls.txt */
void	redirect_input(t_prg *prg, int i, char **envp, char **av)
{
	int	infile;

	infile = open(prg->all_token[i], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (infile == -1)
		error_nl(prg, "unable to open file");
	prg->av_execve = av;
	prg->av_execve[i] = NULL;
	prg->av_execve[i - 1] = NULL;
	execute_single_command(prg, envp, infile, av);
}

/* Main function for redirections */
/* Examples */
/* pwd >> file.txt */
/* ls > file.txt */
/* cat < file.txt */
int	redirections(t_prg *prg, char **envp)
{
	int	i;

	i = 0;
	while (prg->all_token[i] != NULL && (prg->all_token[i + 1] != NULL))
	{
		if (ft_strcmp(prg->all_token[i], ">>") == 0)
		{
			redirect_append(prg, i + 1, envp, prg->all_token);
			return (1);
		}
		else if (ft_strcmp(prg->all_token[i], ">") == 0)
		{
			redirect_input(prg, i + 1, envp, prg->all_token);
			return (1);
		}
		else if (ft_strcmp(prg->all_token[i], "<") == 0)
		{
			redirect_output(prg, i + 1, envp, prg->all_token);
			return (1);
		}
		i++;
	}
	return (0);
}
