/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 16:49:20 by plau              #+#    #+#             */
/*   Updated: 2022/12/30 13:24:54 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Go to new line- invalid command */
// void	new_line(t_prg *prg)
// {
// 	read_command(prg);
// }

/* Prints error and go to new line */
void	error_nl(t_prg *prg, char *str)
{
	perror(str);
	read_command(prg);
}
