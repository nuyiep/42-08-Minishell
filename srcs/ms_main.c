/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:42:23 by plau              #+#    #+#             */
/*   Updated: 2023/03/30 13:41:25 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Start of the main function */
int	main(int ac, char **av, char **envp)
{
	t_prg	prg;

	g_error = 0;
	init_struct(&prg);
	init_envp(&prg, envp);
	shell_loop(&prg, prg.ls_envp);
	if (prg.ls_envp)
		ft_freesplit(prg.ls_envp);
	ft_printf("BYE BYE\n");
	// system("leaks -q minishell");
	(void)ac;
	(void)av;
}
