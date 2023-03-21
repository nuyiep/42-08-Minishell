/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:26:40 by plau              #+#    #+#             */
/*   Updated: 2023/03/21 23:18:50 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_redirection_builtins(t_prg *prg, char **av)
{
	int	i;

	i = 0;
	while (av[i] != NULL)
	{
		if (ft_strcmp(av[i], "<<") == 0)
			ms_heredoc(prg, av);
		i++;
	}
}
