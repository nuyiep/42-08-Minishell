/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:42:23 by plau              #+#    #+#             */
/*   Updated: 2023/03/22 19:21:54 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Start of the main function */
int	main(int ac, char **av, char **envp)
{
	t_prg	prg;

	setup_signal();
	init_envp(&prg, envp);
	shell_loop(&prg, envp);
	if (prg.ls_envp)
		ft_freesplit(prg.ls_envp);
	ft_printf("BYE BYE\n");
	system("leaks -q minishell");
	(void)ac;
	(void)av;
}
