/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:40:00 by plau              #+#    #+#             */
/*   Updated: 2023/04/04 18:18:23 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Built-in exit */
void	ms_exit(t_prg *prg)
{
	ft_printf("exit\n");
	if (prg->all_token[1])
		g_error = ft_atoi(prg->all_token[1]);
	exit(g_error);
}
