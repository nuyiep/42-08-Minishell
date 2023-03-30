/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:49:27 by nchoo             #+#    #+#             */
/*   Updated: 2023/03/30 16:01:05 by nchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_syntax(char **av)
{
	int	i;
	int j;

	i = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (has_operators(av[i][j], "><"))
			{
				if (!av[i + 1])
				{
					exit_code = 268;
					ft_printf("syntax error near unexpected token 'newline'\n");
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}