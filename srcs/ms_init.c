/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 20:02:19 by plau              #+#    #+#             */
/*   Updated: 2022/12/27 20:56:36 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Initialize struct */
void	init_struct(t_prg *prg, char **av, int ac, char **envp)
{
	prg->input = 0;
	prg->npath = 0;
	prg->av = av;
	prg->ac = ac;
	prg->ls_envp = envp;
}
