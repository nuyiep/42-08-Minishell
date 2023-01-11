/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_shell_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:42:57 by plau              #+#    #+#             */
/*   Updated: 2023/01/11 18:37:38 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Main function to read command */
int	read_command(t_prg *prg)
{	
	if (prg->input)
		free(prg->input);
	prg->input = readline("$> ");
	if (prg->input == NULL)
		return (-1);
	add_history(prg->input);
	return (0);
}

/* Main function to parse command */
int	parsing(t_prg *prg)
{
	if (prg->token.all_token)
		ft_freesplit(prg->token.all_token);
	prg->token.all_token = ft_split(prg->input, ' ');
	return (0);
}

/* Main function to execute command */
int	get_data(t_prg *prg, char **envp)
{
	if (ft_strcmp(prg->token.cmd1, "") == 0)
		return (0);
	get_address_one(prg);
	return (0);
	(void)envp;
}

/* Main function for shell loop */
void	shell_loop(t_prg *prg, char **envp)
{
	while (1)
	{
		if (read_command(prg) == -1)
			break ;
		parsing(prg);
		get_data(prg, envp);
		system("leaks -q minishell");
		if (builtins(prg, envp))
			continue ;
	}
	ft_printf("bye\n");
}
