/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_shell_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:42:57 by plau              #+#    #+#             */
/*   Updated: 2022/12/26 22:00:42 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Main function to read command */
/* Sucess return 0  */
/* Fail to read or reach EOF return -1 */
int	read_command(t_prg *prg)
{	
	prg->input = readline("$> ");
	if (prg->input == NULL)
		return (-1);
	return (0);
}

/* Main function to parse command */
/* Fail return -1 */
int	parse_command(t_prg *prg)
{
	prg->cmd = ft_split(prg->input, ' ');
	get_command();
	return (0);
}

/* Main function to execute command */
/* Success return 0 */
/* Fail return -1 */
int	execute_command(t_prg *prg, char **envp)
{
	if (ft_strcmp(prg->cmd[0], "") == 0)
		return (0);
	get_path(prg, envp);
	get_address(prg);
	//child_process(prg, envp);
	return (0);
}

/* Main function for shell loop */
void	shell_loop(t_prg *prg, char **envp)
{
	while (1)
	{
		if (read_command(prg) == -1)
			break ;
		parse_command(prg);
		execute_command(prg, envp);
	}
	ft_printf("bye");
}
