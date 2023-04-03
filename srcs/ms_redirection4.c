/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirection4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 19:29:59 by plau              #+#    #+#             */
/*   Updated: 2023/04/03 22:50:43 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* THIS FILE IS TO HANDLE MULTIPLE < */

/* E.g. cat < file1 < file2 < file3  */
/* Only consider the last file	     */
/* Mixed cases: 		 			 */
/* sort < inputfile.txt > outfile >> log.txt  */
/*  cat (< file1 < file2 > file3 < file4 >) file5 */

char	**remake_av_output(t_prg *prg, char **av, int last_file_position)
{
	int		i;
	char	**trimmed_av;
	int		j;
	int		k;

	i = 0;
	trimmed_av = av;
	while (i < prg->first_symbol_pos_output)
	{
		trimmed_av[i] = av[i];
		i++;
	}
	k = i;
	j = last_file_position;
	while (k < j)
		free(av[k++]);
	trimmed_av[i] = av[j];
	i++;
	trimmed_av[i] = NULL;
	return (trimmed_av);
}

/* Check whether all files exist 	 */
/* count symbol to trim av 		 	 */
/* Return value i is the postion of last file */
int	countsymbols_and_checkfile(t_prg *prg, char **av)
{
	int	i;
	int	infile;

	i = 0;
	while (av[i] != NULL && (av[i + 1] != NULL))
	{
		if (ft_strcmp(av[i], "<") == 0)
		{
			if (prg->first_symbol_pos_output == -1)
				prg->first_symbol_pos_output = i;
			infile = open(av[i + 1], O_RDONLY, 0644);
			prg->total_redir_output++;
			if (infile == -1)
			{
				g_error = 1;
				printf("%s: NNo such file or directory\n", av[i + 1]);
				return (-20);
			}
		}
		i++;
	}
	return (i);
}

void	multiple_output(t_prg *prg, char **av, int i, int **fd)
{
	int	status;
	int	outfile;

	outfile = open(av[i], O_RDONLY, 0644);
	if (fork() == 0)
	{
		if (outfile == -1)
		{
			g_error = 1;
			error_nl(prg, av[i]);
		}
		redirect_output2(prg, i, fd, av);
	}
	else
	{
		close(outfile);
		waitpid(-1, &status, WUNTRACED);
		if (WIFEXITED(status))
			g_error = (WEXITSTATUS(status));
		if (WIFSIGNALED(status))
			g_error = 130;
	}
}

/* Part of the redirect_output function */
/* Separate to comply with norminette */
/* To handle multiple < */
/* PS: can only run with same symbol <  */
int	redirect_output3(t_prg *prg, char **av, int **fd)
{
	int		last_file_position;
	char	**trimmed_av;

	last_file_position = countsymbols_and_checkfile(prg, av);
	if (g_error == 1 && last_file_position == -20)
		return (1);
	if (prg->total_redir_output > 1)
	{
		trimmed_av = remake_av_output(prg, av, last_file_position);
		multiple_output(prg, trimmed_av, last_file_position, fd);
		return (1);
	}
	return (0);
}
