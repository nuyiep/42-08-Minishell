/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_shell_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:42:57 by plau              #+#    #+#             */
/*   Updated: 2023/03/10 18:03:59 by nchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* test function */
static void print_tokens(t_prg *prg)
{
	char **tokens;
	int i = 1;
	
	tokens = prg->all_token;
	if (!*tokens)
		ft_printf("error");
	while (*tokens)
	{
		ft_printf("token #%d: %s\n", i++, *tokens);
		tokens++;
	}
}

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
	prg->all_token = split_token(prg);
	print_tokens(prg);
	// prg->all_token = ft_split(prg->input, ' ');
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
		if (builtins(prg, envp))
			continue ;
	}

	/*
	int i = 0;
	while (prg->all_token[i]) {
		ft_printf("%s [%d]\n", prg->all_token[i], i);
		i++;
	}
	*/
	ft_printf("bye\n");
}
