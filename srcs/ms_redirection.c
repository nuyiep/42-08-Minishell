/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:49:30 by plau              #+#    #+#             */
/*   Updated: 2023/03/30 13:41:17 by plau             ###   ########.fr       */
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
	if ((ft_strncmp(av[0], "/", 1) != 0))
	{
		get_path(prg, prg->ls_envp);
		find_npath(prg);
		av_zero = cmd_access(prg, av[0]);
	}
	dup2(infile, STDOUT_FILENO);
	close(infile);
	execve(av_zero, prg->av_execve, envp);
	error_nl(prg, av_zero);
	return (1);
}

void	wait_redirection(void)
{
	int	status;

	waitpid(0, &status, WUNTRACED);
	if (WIFEXITED(status))
		g_error = (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		g_error = 130;
}

/* pwd >> file.txt - redirect append */
void	redirect_append(t_prg *prg, int i, char **av)
{
	int	infile;

	infile = open(av[i], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fork() == 0)
	{
		if (infile == -1)
		{
			g_error = 2;
			error_nl(prg, prg->all_token[i]);
		}
		prg->av_execve = NULL;
		prg->av_execve = av;
		free(prg->av_execve[i]);
		free(prg->av_execve[i - 1]);
		prg->av_execve[i - 1] = NULL;
		if (ft_execute_redirection(infile, prg->ls_envp, prg, av))
			return ;
	}
	else
		wait_redirection();
}

/* ls > ls.txt - redirect input */
void	redirect_input(t_prg *prg, int i, char **av)
{
	int	infile;

	infile = open(av[i], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fork() == 0)
	{
		if (infile == -1)
		{
			g_error = 1;
			error_nl(prg, prg->all_token[i]);
		}
		prg->av_execve = av;
		free(prg->av_execve[i]);
		free(prg->av_execve[i - 1]);
		prg->av_execve[i - 1] = NULL;
		if (ft_execute_redirection(infile, prg->ls_envp, prg, av))
			return ;
	}
	else
		wait_redirection();
}

/* Main function for redirections */
/* Examples */
/* pwd >> file.txt - redirect append */
/* ls > file.txt - redirect input */
/* cat < file.txt -redirect output */
int	redirections(t_prg *prg)
{
	int	i;
	int	**fd;

	i = 0;
	prg->cmd_pos = 0;
	fd = NULL;
	while (prg->all_token[i] != NULL && (prg->all_token[i + 1] != NULL))
	{
		if (ft_strcmp(prg->all_token[i], ">>") == 0)
		{
			redirect_append(prg, i + 1, prg->all_token);
			return (1);
		}
		else if (ft_strcmp(prg->all_token[i], ">") == 0)
		{
			redirect_input(prg, i + 1, prg->all_token);
			return (1);
		}
		else if (ft_strcmp(prg->all_token[i], "<") == 0)
			return (redirect_output(prg, i + 1, prg->all_token, fd));
		i++;
	}
	return (0);
}
