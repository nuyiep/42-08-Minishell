/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:26:40 by plau              #+#    #+#             */
/*   Updated: 2023/03/22 21:09:38 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Piping's heredoc not mentioned in the subject */
int	check_redirection_builtins(t_prg *prg, char **av)
{
	int	i;

	i = 0;
	while (av[i] != NULL)
	{
		if (ft_strcmp(av[i], "<<") == 0)
		{
			ms_heredoc(prg, av);
			return (1);
		}
		else if (ft_strcmp(av[i], ">>") == 0)
		{
			redirect_append(prg, i + 1, av);
			return (1);
		}
		else if (ft_strcmp(av[i], ">") == 0)
		{
			redirect_input(prg, i + 1, av);
			return (1);
		}
		else if (ft_strcmp(av[i], "<") == 0)
			return (redirect_output(prg, i + 1, av));
		i++;
	}
	return (0);
}
