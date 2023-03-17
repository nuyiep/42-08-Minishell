/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 16:49:20 by plau              #+#    #+#             */
/*   Updated: 2023/03/16 15:21:46 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Prints error and go to new line */
void	error_nl(t_prg *prg, char *str)
{
	perror(str);
	read_command(prg);
}
