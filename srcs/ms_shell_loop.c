/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_shell_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:42:57 by plau              #+#    #+#             */
/*   Updated: 2022/12/27 21:46:02 by plau             ###   ########.fr       */
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
	prg->cmd = ft_split(prg->input, ' ');
	ms_parse(prg);
	return (0);
}

/* Main function to execute command */
	// child_process(prg, envp);
int	execute_command(t_prg *prg, char **envp)
{
	if (ft_strcmp(prg->cmd[0], "") == 0)
		return (0);
	get_path(prg, envp);
	get_address(prg);
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
		builtins(prg);
		execute_command(prg, envp);
	}
	ft_printf("bye\n");
}

/* Main function for builtins */
void	builtins(t_prg *prg)
{
	pwd(prg);
	print_env(prg);
}
