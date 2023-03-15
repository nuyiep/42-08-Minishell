/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 20:02:19 by plau              #+#    #+#             */
/*   Updated: 2023/03/13 20:29:43 by nchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Make a copy of env and save into struct */
static void	init_envp(t_prg *prg, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	prg->ls_envp = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (envp[++i])
		prg->ls_envp[i] = ft_strdup(envp[i]);
	prg->ls_envp[i] = NULL;
}

static void	init_exp(t_prg *prg)
{
	prg->exp = malloc(sizeof(t_prg));
	prg->exp->pair = NULL;
	prg->exp->key = NULL;
	prg->exp->value = ft_strdup(" ");
	prg->exp->quote = 0;
}

/* Initialize struct */
void	init_struct(t_prg *prg, char **av, int ac, char **envp)
{
	init_envp(prg, envp);
	init_exp(prg);
	prg->input = 0;
	prg->all_token = NULL;
	(void)ac;
	(void)av;
}
