/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 20:35:47 by plau              #+#    #+#             */
/*   Updated: 2023/01/17 16:38:20 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Check whether key has value */
int	got_value(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

/* To print the list of env */
void	env(t_prg *prg)
{
	int	i;

	i = 0;
	while (prg->ls_envp[i] != NULL)
	{
		if (got_value(prg->ls_envp[i]))
			ft_printf("%s\n", prg->ls_envp[i]);
		i++;
	}
}
