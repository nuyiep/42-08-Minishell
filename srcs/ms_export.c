/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:39:53 by plau              #+#    #+#             */
/*   Updated: 2023/01/02 15:47:25 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// export PANDA=cute
// env PANDA (will print cute)
// exit

/* If export is called without any arguments, print env */
/* Otherwise, add the given variables to the env variables */
void	export(t_prg *prg)
{
	if (prg->token.all_token[1] == NULL)
		env(prg);
	else
	{
		ft_printf("\nchecking here\n\n");
		//ft_printf("%d\n", prg->n_env);
		prg->ls_envp[prg->n_env] = prg->token.all_token[1];
		env(prg);
	}
}