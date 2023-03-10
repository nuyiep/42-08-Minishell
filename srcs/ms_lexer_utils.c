/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 00:50:42 by nchoo             #+#    #+#             */
/*   Updated: 2023/03/11 00:51:30 by nchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		{
			// ft_printf("i: %d\n", i);
			return (i + 1);
		}
		i++;
		temp++;
	}
	return (0);
}