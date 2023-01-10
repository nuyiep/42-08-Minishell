/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_shell_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:42:57 by plau              #+#    #+#             */
/*   Updated: 2023/01/10 14:27:41 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Main function to read command */
int	read_command(t_prg *prg)
{	
	prg->input = readline("$> ");
	if (prg->input == NULL)
		return (-1);
	add_history(prg->input);
	return (0);
}

/* Main function to parse command */
int	parsing(t_prg *prg)
{
	init_token(prg);
	return (0);
}

/* Main function to execute command */
	// child_process(prg, envp);
int	get_data(t_prg *prg, char **envp)
{
	if (ft_strcmp(prg->token.cmd1, "") == 0)
		return (0);
	get_path(prg, envp);
	get_address_one(prg);
	get_address_two(prg);
	return (0);
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
		if (builtins(prg, envp))
			continue ;
		if (prg->fd_in != -3)
			check_open(prg);
		if (prg->cmdpath2 == NULL)
		{
			execve(prg->cmdpath1, prg->token.all_cmd1, envp);
			continue ;
		}
		create_child(prg);
	}
	ft_printf("bye\n");
}
