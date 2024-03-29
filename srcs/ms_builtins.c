/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:27:06 by plau              #+#    #+#             */
/*   Updated: 2023/03/31 21:45:54 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Part of builtins function- To comply with norminette */
int	builtins_2(t_prg *prg, char **envp, char **av)
{
	if (ft_strcmp(av[0], "cd") == 0)
	{
		cd(prg, envp);
		return (1);
	}
	if (ft_strcmp(av[0], "unset") == 0)
	{
		unset(prg);
		return (1);
	}
	if (ft_strcmp(av[0], "exit") == 0)
	{
		ms_exit(prg);
		return (1);
	}	
	else
		return (0);
}

/* Main function for builtins */
int	builtins(t_prg *prg, char **envp, char **av)
{
	if (ft_strcmp(av[0], "pwd") == 0)
	{
		pwd(prg);
		return (1);
	}
	if (ft_strcmp(av[0], "echo") == 0)
	{
		echo(prg, av);
		return (1);
	}
	if (ft_strcmp(av[0], "env") == 0)
	{
		env(prg);
		return (1);
	}
	if (ft_strcmp(av[0], "export") == 0)
	{
		ms_export(prg);
		return (1);
	}
	else
		return (builtins_2(prg, envp, av));
}
