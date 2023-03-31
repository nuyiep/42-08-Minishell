/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:49:27 by nchoo             #+#    #+#             */
/*   Updated: 2023/03/31 19:11:21 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax(char **av)
{
	int	i;
	int	j;

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
					g_error = 258;
					ft_printf("syntax error near unexpected token `newline'\n");
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_quotes(t_prg *prg)
{
	int		i;
	int		j;
	char	**tokens;

	tokens = prg->all_token;
	i = 0;
	while (tokens[i])
	{
		j = 0;
		while (tokens[i][j] && tokens[i][j + 1])
		{
			if (has_operators(tokens[i][j], "\'\""))
			{
				if (!has_pair_first(tokens[i], j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
