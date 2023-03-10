/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:30:56 by plau              #+#    #+#             */
/*   Updated: 2023/03/10 11:55:36 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Create pipes for each pair of commands */
void	do_pipex(t_prg *prg, char **envp)
{
	int		**fd;
	char	**tokens;
	int		i;
	
	i = 0;
	tokens = prg->all_token;
	while (*tokens != NULL)
		i++;
	printf("i = %d\n", i);
	// fd = make_pipes(prg->all_token);
	(void)envp;
	(void)fd;
}
