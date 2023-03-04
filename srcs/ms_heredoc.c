/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:44:45 by plau              #+#    #+#             */
/*   Updated: 2023/03/04 16:23:00 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_heredoc(t_prg *prg, char **heredoc_input)
{
	int	i;

	i = 0;
	while (*heredoc_input)
	{
		printf("%s\n", heredoc_input[i]);
		i++;
	}
	(void)prg;
}

/* Main function for heredoc */
/* (Later) Creates a temp file to store what's read from the stdin */
/* codes written based on the structure: */
/* cat << eof */
/* $heredoc> hello */
void	heredoc_main(t_prg *prg, char **av, char **envp)
{
	char	*delimiter;
	// char	*cat;
	char	**heredoc_input;
	int		i;

	if (ft_strcmp("<<", prg->all_token[1]) != 0)
		return ;
	delimiter = prg->all_token[2];
	heredoc_input = NULL;
	i = 0;
	while (1)
	{
		heredoc_input[i] = readline("$>heredoc>> ");
		if (heredoc_input[i] == NULL)
		{
			ft_freesplit(heredoc_input);
			return ;
		}
		if (ft_strncmp(heredoc_input[i], delimiter, ft_strlen(delimiter)) == 0)
			break ;
		i++;
	}
	write_heredoc(prg, heredoc_input);
	ft_freesplit(heredoc_input);
	(void)av;
	(void)envp;
	return ;
}
