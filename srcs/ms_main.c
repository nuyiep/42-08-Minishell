/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:42:23 by plau              #+#    #+#             */
/*   Updated: 2023/04/03 22:44:52 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Initialize struct */
void	init_struct(t_prg *prg)
{
	prg->input = 0;
	prg->all_token = NULL;
	prg->no_pipes = 0;
	prg->heredoc = 0;
	prg->heredoc_postion = 0;
	prg->av_execve = NULL;
	prg->npath = 0;
	prg->path = NULL;
	prg->cmd_pos = -1;
	prg->total_redir_append_output = 0;
	prg->last_file_pos = 0;
	prg->first_redir_symbol_pos = 0;
	prg->total_redir_output = 0;
	prg->first_symbol_pos_output = -1;
}

/* Start of the main function */
int	main(int ac, char **av, char **envp)
{
	t_prg	prg;
	int		value;

	g_error = 99;
	value = 0;
	init_struct(&prg);
	init_envp(&prg, envp);
	shell_loop(&prg, prg.ls_envp, value);
	if (prg.ls_envp)
		ft_freesplit(prg.ls_envp);
	ft_printf("BYE BYE\n");
	free_exp(&prg);
	(void)ac;
	(void)av;
	system("leaks -q minishell");
}
