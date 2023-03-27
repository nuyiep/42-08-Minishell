/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 00:50:42 by nchoo             #+#    #+#             */
/*   Updated: 2023/03/27 16:17:51 by nchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int has_operators(char c, char *op)
{
	int j;

	j = 0;
	while (op[j])
	{
		if (op[j] == c)
			return 1;
	j++;
	}
	return (0);
}

int has_pair_first(char *s)
{
	char *temp;
	char pair;
	int i;

	i = 1;
	temp = s;
	pair = *temp;
	temp++;
	while (*temp)
	{
		if (*temp == pair)
			return (i + 1);
		i++;
		temp++;
	}
	return (0);
}

int has_pair(char *s)
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
			return (i + 1);
		i++;
		temp++;
	}
	return (0);
}