/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 18:27:26 by plau              #+#    #+#             */
/*   Updated: 2023/03/11 16:23:07 by nchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Check whether (-n) flag is correct
OK: -n -nnn echo (1) 
KO: n -na --n -n-n (0) */
int	check_flag(char *arg)
{
	int	i;

	i = 0;
	if (arg == NULL)
		return (0);
	if (arg[i] != '-')
		return (0);
	while (arg[++i] != '\0')
	{
		if (arg[i] != 'n')
			return (0);
	}
	return (1);
}	

/* Echo with \n */
/* echo -nnn -n -n -n hello  - OK */
/* echo -nnnn -n -n -nb hello - Nope */
void	echo(t_prg *prg, char **input)
{
	int	i;

	i = 1;
	if (ft_strcmp(input[0], "echo") != 0)
		return ((void)prg);
	while (input[i])
	{
		if (check_flag(input[i]) == 0)
			break ;
		i++;
	}
	while (input[i])
	{
		{
			ft_printf("%s", input[i]);
			if (input[i + 1] != 0)
				ft_printf(" ");
		}
		i++;
	}
	if (check_flag(input[1]) == 0)
		ft_printf("\n");
}
	/*
		check if echo command
		int i = 1;
		
		while (still got arguments (not NULL))
		{
			if (check_flag(av[i]) == 0)
				break ;
		}
		while (still got arguemnts (not NULL))
		{
			print(av[i]);
			if (argument + 1 is not NULL)
				print(" ")
		}
		if (check_flag(av[1]) == 0)
			print("\n");
	*/
