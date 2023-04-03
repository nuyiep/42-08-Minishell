/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:49:30 by plau              #+#    #+#             */
/*   Updated: 2023/04/03 15:59:30 by plau             ###   ########.fr       */
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

/* ls -l (> file.txt) >> outfile.txt */
char	**remake_av(t_prg *prg, char **av)
{
	int		i;
	char	**trimmed_av;
	int		j;
	int		k;

	i = 0;
	trimmed_av = av;
	while (i < prg->first_redir_symbol_pos)
	{
		trimmed_av[i] = av[i];
		i++;
	}
	j = prg->last_file_pos - 1;
	k = i;
	while (k < j)
		free(av[k++]);
	while (av[j] != NULL)
	{
		trimmed_av[i] = av[j];
		i++;
		j++;
	}
	prg->last_file_pos = i - 1;
	trimmed_av[i] = NULL;
	return (trimmed_av);
}

/* pwd >> file.txt - redirect append */
/* ls > file.txt >> outfile.txt */
/* i - position of the file */
void	redirect_append(t_prg *prg, int i, char **av)
{
	int	infile;

	infile = open(av[i], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fork() == 0)
	{
		if (infile == -1)
		{
			g_error = 2;
			error_nl(prg, av[i]);
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

/* PS: naming is different from subject pdf */
/* 		< 		redirect input 				*/
/* 		<< 		heredoc 					*/
/* 		> 		redirect output 			*/
/* 		>> 		redirect output append 		*/
/*	To handle e.g. pwd > file > outfile		*/
void	countsymbols_and_openfile(t_prg *prg, char **av)
{
	int	i;
	int	redir_append;
	int	redir_output;
	int	redir_append_pos;
	int	redir_output_pos;

	i = 0;
	redir_append = 0;
	redir_output = 0;
	redir_append_pos = 0;
	redir_output_pos = 0;
	while (av[i] != NULL && (av[i + 1] != NULL))
	{
		if (ft_strcmp(av[i], ">>") == 0)
		{
			open(av[i + 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
			redir_append++;
			redir_append_pos = i;
		}
		else if (ft_strcmp(av[i], ">") == 0)
		{
			open(av[i + 1], O_CREAT, 0644);
			redir_output++;
			redir_output_pos = i;
		}
		i++;
	}
	prg->total_redir_append_output = redir_append + redir_output;
	if (redir_append_pos > redir_output_pos)
	{
		prg->last_file_pos = redir_append_pos + 1;
		prg->last_redir_symbol = ">>";
	}
	else
	{
		prg->last_file_pos = redir_output_pos + 1;
		prg->last_redir_symbol = ">";
	}
}

void	find_first_redir_symbol_pos(t_prg *prg, char **av)
{
	int	i;

	i = 0;
	while (av[i] != NULL)
	{
		if (ft_strcmp(av[i], ">>") == 0)
		{
			prg->first_redir_symbol_pos = i;
			return ;
		}
		else if (ft_strcmp(av[i], ">") == 0)
		{
			prg->first_redir_symbol_pos = i;
			return ;
		}
		i++;
	}
}

/* Main function for redirections */
/* Examples */
/* pwd >> file.txt - redirect append */
/* ls > file.txt - redirect input */
/* cat < file.txt -redirect output */
/* pwd > file.txt >> outfile.txt */
/* sort < inputfile.txt > outfile >> log.txt */
int	redirections(t_prg *prg)
{
	int	i;
	int	**fd;

	i = 0;
	prg->cmd_pos = 0;
	fd = NULL;
	countsymbols_and_openfile(prg, prg->all_token);
	find_first_redir_symbol_pos(prg, prg->all_token);
	if (prg->total_redir_append_output > 1)
		remake_av(prg, prg->all_token);
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
