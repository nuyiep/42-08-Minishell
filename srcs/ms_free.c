/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:09:05 by nchoo             #+#    #+#             */
/*   Updated: 2023/03/31 15:24:27 by nchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exp(t_prg *prg)
{
	if (prg->exp->pair)
		ft_freesplit(prg->exp->pair);
	if (prg->exp->key)
	{
		free(prg->exp->key);
		prg->exp->key = NULL;
	}
	if (prg->exp->value)
		free(prg->exp->value);
	free(prg->exp);
}
