/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 16:49:20 by plau              #+#    #+#             */
/*   Updated: 2023/03/25 13:43:10 by nchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Prints error and go to new line */
void	error_nl(t_prg *prg, char *str)
{
	exit_code = 1;
	perror(str);
	read_command(prg);
}
