/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirection2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:48:23 by plau              #+#    #+#             */
/*   Updated: 2023/03/15 17:43:29 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_redirection_output(int outfile, char **envp, t_prg *prg, int i)
{
	if ((ft_strncmp(prg->all_token[0], "/", 1) != 0))
	{
		get_path(prg, envp);
		find_npath(prg);
		cmd_access(prg);
	}
	char *arguments = "cat ls.txt";
	char **split = ft_split(arguments, ' ');
	execve(prg->all_token[0], split, envp);
	error_nl(prg, prg->all_token[2]);
	return (1);
	(void)outfile;
	(void)i;
	
}

void	execute_single_command_output(t_prg *prg, char **envp, int outfile, int i)
{
	if (fork() == 0)
	{
		if (ft_execute_redirection_output(outfile, envp, prg, i))
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
	execute_single_command_output(prg, envp, outfile, i);
}
