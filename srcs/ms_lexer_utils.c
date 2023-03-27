/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 00:50:42 by nchoo             #+#    #+#             */
/*   Updated: 2023/03/27 14:10:42 by nchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int has_operators(char *s, char *op)
{
	int i;
	int j;
	
	i = 0;
	while (s[i])
	{
		j = 0;
		while (op[j])
		{
			if (s[i] == op[j])
				return 1;
		j++;
		}
		i++;
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