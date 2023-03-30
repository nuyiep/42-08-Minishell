/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 16:49:20 by plau              #+#    #+#             */
/*   Updated: 2023/03/29 21:35:42 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Prints error and go to new line */
void	error_nl(t_prg *prg, char *str)
{
	if (prg->all_token[1] == NULL)
		printf("%s: command not found\n", str);
	else
		perror(str);
	exit(g_error);
}
