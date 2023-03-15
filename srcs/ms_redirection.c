/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:49:30 by plau              #+#    #+#             */
/*   Updated: 2023/03/15 16:43:54 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_redirection(int infile, char **envp, t_prg *prg)
{
	dup2(infile, STDOUT_FILENO);
	close(infile);
	if ((ft_strncmp(prg->all_token[0], "/", 1) != 0))
	{
		get_path(prg, envp);
		find_npath(prg);
		cmd_access(prg);
	}
	char *arguments = "ls ";
	char **split = ft_split(arguments, ' ');
	execve(prg->all_token[0], split, envp);
	error_nl(prg, prg->all_token[0]);
	return (1);
}

void	execute_single_command(t_prg *prg, char **envp, int infile)
{
	if (fork() == 0)
	{
		if (ft_execute_redirection(infile, envp, prg))
			return ;
	}
	else
	{
		close(infile);
		while (waitpid(-1, NULL, 0) != -1)
			;
	}
	return ;
}

/* ls > ls.txt */
void	redirect_append(t_prg *prg, int i, char **envp)
{
	int	infile;

	infile = open(prg->all_token[i], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (infile == -1)
		error_nl(prg, "unable to open file");
	execute_single_command(prg, envp, infile);
}

// void	redirect_output(t_prg *prg, int i, char **envp)
// {
	
// }

/* Main function for redirections */
int	redirections(t_prg *prg, char **envp)
{
	int	i;

	i = 0;
	while (prg->all_token[i] != NULL && (prg->all_token[i + 1] != NULL))
	{
		if (ft_strcmp(prg->all_token[i], ">>") == 0)
		{
			redirect_append(prg, i + 1, envp);
			return (1);
		}
		// else if (ft_strcmp(prg->all_token[i], "<"))
		// {
		// 	redirect_output(prg, i, envp);
		// }
		// else if (ft_strcmp(prg->all_token[i], ">>"))
		// {
		// 	redirect_output_append(prg, i, envp);
		// }
		i++;	
	}
	return (0);
}

/* Examples */
/* ls > ls.txt */
/* cat < ls.txt */
/* pwd >> ls.txt */
