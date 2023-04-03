/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:26:40 by plau              #+#    #+#             */
/*   Updated: 2023/04/03 18:58:16 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Check whether there's any redirection symbols */
int	check_redirection_builtins(t_prg *prg, char **av, int **fd)
{
	int	i;

	i = 0;
	countsymbols_and_openfile(prg, av);
	find_first_redir_symbol_pos(prg, av);
	if (prg->total_redir_append_output > 1)
		remake_av(prg, av);
	while (av[i] != NULL && av[i + 1] != NULL)
	{
		if (ft_strcmp(av[i], "<<") == 0)
		{
			ms_heredoc(prg, av);
			return (1);
		}
		else if (ft_strcmp(av[i], ">>") == 0)
			return (redirect_append(prg, i + 1, av));
		else if (ft_strcmp(av[i], ">") == 0)
			return (redirect_input(prg, i + 1, av));
		else if (ft_strcmp(av[i], "<") == 0)
			return (redirect_output(prg, i + 1, av, fd));
		i++;
	}
	return (0);
}
