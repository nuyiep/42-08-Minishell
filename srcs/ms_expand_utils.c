/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:29:40 by nchoo             #+#    #+#             */
/*   Updated: 2023/03/27 14:34:50 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_var(char *token, int i)
{
	char *var;
	int j;
	
	j = 0;
	while (token[i] && token[i] != ' ' \
	&& token[i] != '\'' && token[i] != '\"')
	{
		j++;
		i++;
	}
	var = malloc(sizeof(char) * (j + 1));
	i -= j;
	j = 0;
	while (token[i] && token[i] != ' ' \
	&& token[i] != '\'' && token[i] != '\"')
		var[j++] = token[i++];
	var[j] = '\0';
	//ft_printf("var: %s\n", var);
	return (var);
}