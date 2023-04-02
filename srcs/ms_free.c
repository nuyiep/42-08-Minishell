/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:09:05 by nchoo             #+#    #+#             */
/*   Updated: 2023/03/31 21:50:57 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Free exp */
void	free_exp(t_prg *prg)
{
	if (prg->exp->pair)
		ft_freesplit(prg->exp->pair);
	if (prg->exp->key)
		free(prg->exp->key);
	if (prg->exp->value)
		free(prg->exp->value);
	free(prg->exp);
}
