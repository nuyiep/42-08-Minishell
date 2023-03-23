/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 00:50:42 by nchoo             #+#    #+#             */
/*   Updated: 2023/03/23 12:35:29 by nchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int has_pair_first(char *s, t_prg *prg)
{
	char *temp;
	char pair;
	int i;

	i = 1;
	temp = s;
	pair = *temp;
	ft_printf("pair: %c\n", pair);
	temp++;

	while (*temp)
	{
		if (*temp == pair)
		{
			if (*temp == '\'')
				prg->exp->quote = 1;
			if (*temp == '\"')
				prg->exp->quote = 2;
			return (i + 1);
		}
		i++;
		temp++;
	}
	return (0);
}

int has_pair(char *s, t_prg *prg)
{
	char *temp;
	char pair;
	int i;

	i = 1;
	temp = s;
	temp++;
	pair = *temp;
	temp++;

	while (*temp)
	{
		if (*temp == pair)
		{
			if (*temp == '\'')
				prg->exp->quote = 1;
			if (*temp == '\"')
				prg->exp->quote = 2;
			return (i + 1);
		}
		i++;
		temp++;
	}
	return (0);
}