/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:27:06 by plau              #+#    #+#             */
/*   Updated: 2023/01/17 15:17:14 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtins_2(t_prg *prg, char **envp)
{
	if (ft_strcmp(prg->token.all_token[0], "cd") == 0)
	{
		cd(prg, envp);
		return (1);
	}
	if (ft_strcmp(prg->token.all_token[0], "unset") == 0)
	{
		unset(prg);
		return (1);
	}
	if (ft_strcmp(prg->token.all_token[0], "exit") == 0)
	{
		ms_exit(prg);
		return (1);
	}	
	else
		return (0);
}

/* Main function for builtins */
int	builtins(t_prg *prg, char **envp)
{
	if (ft_strcmp(prg->token.all_token[0], "pwd") == 0)
	{
		pwd(prg);
		return (1);
	}
	if (ft_strcmp(prg->token.all_token[0], "echo") == 0)
	{
		echo(prg, prg->token.all_token);
		return (1);
	}
	if (ft_strcmp(prg->token.all_token[0], "env") == 0)
	{
		env(prg);
		return (1);
	}
	if (ft_strcmp(prg->token.all_token[0], "export") == 0)
	{
		export(prg);
		return (1);
	}
	else
		return (builtins_2(prg, envp));
}
