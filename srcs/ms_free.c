/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:09:05 by nchoo             #+#    #+#             */
/*   Updated: 2023/03/13 17:35:35 by nchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_exp(t_prg *prg, int value)
{
	if (prg->exp->pair)
		ft_freesplit(prg->exp->pair);
	if (prg->exp->key)
	{
		free(prg->exp->key);
		prg->exp->key = NULL;
	}
	if (ft_strncmp(prg->exp->value, " ", 1) && value)
		prg->exp->value = ft_strdup(" ");
	else if (value == 0)
	{
		free(prg->exp->value);
		free(prg->exp);
	}
}