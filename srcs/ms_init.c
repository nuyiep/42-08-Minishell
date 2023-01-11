/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 20:02:19 by plau              #+#    #+#             */
/*   Updated: 2023/01/11 19:28:37 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Initialize struct */
void	init_struct(t_prg *prg, char **av, int ac, char **envp)
{
	int	i;

	i = 1;
	while (envp[i])
		i++;
	prg->ls_envp = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (envp[++i])
		prg->ls_envp[i] = ft_strdup(envp[i]);
	prg->ls_envp[i] = 0;
	prg->input = 0;
	prg->npath = 0;
	prg->av = av;
	prg->ac = ac;
	prg->fd_in = -3;
	prg->fd_out = -3;
	prg->cmdpath2 = NULL;
	prg->ccmd = 1;
	prg->n_env = 0;
	prg->echo_f = 0;
	prg->token.all_token = NULL;
}

/* cat <       |infile|
// grep-n merry_xmas&haooy_mew_year > outfile */

// Only handling this grammar for now
// ls < infile | cat > outfile
// 7 tokens 
/* Initialize tokens */
void	init_token(t_prg *prg)
{
	(void)prg;
}
