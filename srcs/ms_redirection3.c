/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirection3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:37:05 by plau              #+#    #+#             */
/*   Updated: 2023/04/03 19:29:27 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* THIS FILE IS TO HANDLE MULTIPLE >> AND > */

/* Part of the countsymbols_and_openfile function */
/* To comply with norminette 					  */
void	countsymbols_and_openfile2(int redir_append_pos,
		int redir_output_pos, t_prg *prg)
{
	if (redir_append_pos > redir_output_pos)
		prg->last_file_pos = redir_append_pos + 1;
	else
		prg->last_file_pos = redir_output_pos + 1;
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
	int	redir_append_pos;
	int	redir_output_pos;

	i = 0;
	redir_append_pos = 0;
	redir_output_pos = 0;
	prg->total_redir_append_output = 0;
	while (av[i] != NULL && (av[i + 1] != NULL))
	{
		if (ft_strcmp(av[i], ">>") == 0)
		{
			open(av[i + 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
			prg->total_redir_append_output++;
			redir_append_pos = i;
		}
		else if (ft_strcmp(av[i], ">") == 0)
		{
			open(av[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
			prg->total_redir_append_output++;
			redir_output_pos = i;
		}
		i++;
	}
	countsymbols_and_openfile2(redir_append_pos, redir_output_pos, prg);
}

/* Find the first redirection symbol position */
/* Trim out the middle commands 			  */
/* E.g. ls -l (> file.txt) >> outfile.txt 	  */
/* Only left with ls -l >> outfile.txt  	  */
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
