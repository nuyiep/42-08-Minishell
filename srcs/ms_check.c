/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:26:40 by plau              #+#    #+#             */
/*   Updated: 2023/03/21 18:36:03 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_redirection_builtins(t_prg *prg, char **av_one)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (av_one[i] != NULL)
	{
		while (av_one[i][j] != NULL)
		{
			if (av_one[i][j] == '<<')
			{
				ms_heredoc(prg);
			}
			j++;
		}
		i++;
	}
}
