/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_shell_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:42:57 by plau              #+#    #+#             */
/*   Updated: 2023/03/09 21:12:59 by plau             ###   ########.fr       */
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
	if (prg->all_token)
		ft_freesplit(prg->all_token);
	prg->all_token = ft_split(prg->input, ' ');
	return (0);
}

/* Main function for shell loop */
void	shell_loop(t_prg *prg, char **envp, char **av)
{
	while (1)
	{
		if (read_command(prg) == -1)
			break ;
		//lexer(prg, av);
		parsing(prg);
		if (prg->all_token[0] == NULL)
			continue ;
		if (ms_heredoc(prg, av, envp) != 1)
			continue ;
		if (builtins(prg, envp))
			continue ;
		if (executor(prg, av, envp) == 0)
			continue ;
	}
	ft_printf("bye\n");
}
