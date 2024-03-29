/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_shell_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:53:03 by plau              #+#    #+#             */
/*   Updated: 2023/04/01 19:09:44 by plau             ###   ########.fr       */
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
	int	i;
	int	space_tab_count;

	if (prg->input)
		free(prg->input);
	prg->input = readline("$> ");
	if (prg->input == 0)
		return (-1);
	if (prg->input[0] == '\0')
		return (2);
	i = 0;
	space_tab_count = 0;
	while (prg->input[i] != '\0')
	{
		if (prg->input[i] == 32 || prg->input[i] == 9)
			space_tab_count++;
		i++;
	}
	if (i == space_tab_count)
		return (3);
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
	prg->all_token = split_token(prg);
	if (prg->all_token == NULL)
		return (1);
	prg->all_token = expand_tokens(prg);
	if (!check_quotes(prg))
	{
		g_error = 258;
		ft_printf("syntax error\n");
		return (1);
	}
	prg->all_token = remove_all_quotes(prg);
	count_pipe_n_heredoc(prg);
	return (0);
}

void	free_all(t_prg *prg)
{
	if (prg->all_token)
		ft_freesplit(prg->all_token);
	if (prg->path)
		ft_freesplit(prg->path);
	if (prg->input)
		free(prg->input);
	free_exp(prg);
}

/* Main function for shell loop 			*/
/* 		< 		redirect input 				*/
/* 		<< 		heredoc 					*/
/* 		> 		redirect output 			*/
/* 		>> 		redirect output append 		*/
/* PS: naming is different from subject pdf */
void	shell_loop(t_prg *prg, char **envp, int value)
{
	while (1)
	{
		setup_signal();
		if (prg->input)
			free_all(prg);
		init_with_exp(prg);
		value = read_command(prg);
		if (value == -1)
			break ;
		else if (value == 2 || value == 3 || (parsing(prg) == 1))
			continue ;
		if (prg->no_pipes == 0)
		{
			if (ms_heredoc(prg, prg->all_token) == 0)
				;
			else if (redirections(prg) == 1)
				;
			else if (builtins(prg, envp, prg->all_token))
				;
			else if (executor(prg) == 0)
				;
		}
		else
			executor(prg);
	}
}
