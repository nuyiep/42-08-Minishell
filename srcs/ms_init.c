/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 20:02:19 by plau              #+#    #+#             */
/*   Updated: 2023/01/10 13:14:54 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Initialize struct */
void	init_struct(t_prg *prg, char **av, int ac, char **envp)
{
	prg->input = 0;
	prg->npath = 0;
	prg->av = av;
	prg->ac = ac;
	prg->ls_envp = envp;
	prg->fd_in = -3;
	prg->fd_out = -3;
	prg->cmdpath2 = NULL;
	prg->ccmd = 1;
	prg->n_env = 0;
	prg->echo_f = 0;
}

/* cat <       |infile|
// grep-n merry_xmas&haooy_mew_year > outfile */

// Only handling this grammar for now
// ls < infile | cat > outfile
// 7 tokens 
/* Initialize tokens */
void	init_token(t_prg *prg)
{
	prg->token.all_token = ft_split(prg->input, ' ');
	prg->token.cmd1 = prg->token.all_token[0];
	prg->token.all_cmd1 = ft_split(prg->token.cmd1, ' ');
}
