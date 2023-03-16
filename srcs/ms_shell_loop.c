/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_shell_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:42:57 by plau              #+#    #+#             */
/*   Updated: 2023/03/16 14:41:18 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* TEST FUNCTION */

// static void print_tokens(t_prg *prg)
// {
// 	char **tokens;
// 	int i = 1;

// 	tokens = prg->all_token;
// 	if (!*tokens)
// 		ft_printf("error");
// 	while (*tokens)
// 	{
// 		ft_printf("token #%d: %s\n", i++, *tokens);
// 		tokens++;
// 	}
// }

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

/* Check whether there is pipe or heredoc */
void	count_pipe_n_heredoc(t_prg *prg)
{
	int	i;

	i = 0;
	while (prg->all_token[i] != NULL)
	{
		if (ft_strcmp(prg->all_token[i], "|") == 0)
			prg->no_pipes++;
		else if (ft_strcmp(prg->all_token[i], "<<") == 0)
		{
			prg->heredoc++;
			prg->heredoc_postion = i;
		}
		i++;
	}
}

/* Main function to parse command */
int	parsing(t_prg *prg)
{
	if (prg->all_token)
		ft_freesplit(prg->all_token);
	prg->all_token = split_token(prg);
	if (prg->all_token == NULL)
		return (1) ;
	prg->all_token = expand_tokens(prg);
	//print_tokens(prg);
	// prg->all_token = ft_split(prg->input, ' ');
	count_pipe_n_heredoc(prg);
	return (0);
}

/* Main function for shell loop */
/* 		< 		redirect input */
/* 		<< 		heredoc */
/* 		> 		redirect output */
/* 		>> 		redirect output append */
void	shell_loop(t_prg *prg, char **envp, char **av)
{
	while (1)
	{
		if (read_command(prg) == -1)
			break ;
		parsing(prg);
		if (prg->all_token == NULL)
			continue ;
		if (ms_heredoc(prg) == 0)
			continue ;
		if (redirections(prg, envp) == 1)
			continue ;
		if (builtins(prg, envp))
			continue ;
		if (executor(prg, av, envp) == 0)
			continue ;
	}

	/* temporary free */
	if (prg->all_token)
		ft_freesplit(prg->all_token);
	if (prg->ls_envp)
		ft_freesplit(prg->ls_envp);
	free_exp(prg, 0);
	
	ft_printf("bye\n");
	(void)av;
}
