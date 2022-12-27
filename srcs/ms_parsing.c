/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 15:44:42 by plau              #+#    #+#             */
/*   Updated: 2022/12/27 21:46:50 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* cat <       |infile|
grep-n merry_xmas&haooy_mew_year > outfile */
void	ms_parse(t_prg *prg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (prg->cmd[i] != NULL)
		i++;
}
