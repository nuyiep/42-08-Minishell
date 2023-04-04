/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:40:00 by plau              #+#    #+#             */
/*   Updated: 2023/04/04 20:42:18 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	when_i_is_2(int i, t_prg *prg)
{
	if (i == 2)
	{
		i = 0;
		while (prg->all_token[1][i] != '\0')
		{
			if (ft_isdigit(prg->all_token[1][i]) == 1)
				i++;
			else
			{
				ft_printf("exit\n");
				ft_printf("exit: %s: numeric argument required\n",
					prg->all_token[1]);
				g_error = 255;
				exit(g_error);
			}
		}
	}
}

/* Built-in exit */
void	ms_exit(t_prg *prg)
{
	int	i;

	i = 0;
	while (prg->all_token[i])
		i++;
	if (i > 2)
	{
		ft_printf("exit\n");
		ft_printf("exit: too many arguments\n");
		g_error = 1;
		return ;
	}
	when_i_is_2(i, prg);
	if (ft_atoi(prg->all_token[1]) > 256)
		g_error = (ft_atoi(prg->all_token[1]) % 256);
	else
		g_error = ft_atoi(prg->all_token[1]);
	ft_printf("exit\n");
	exit(g_error);
}
