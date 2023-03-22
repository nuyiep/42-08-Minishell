/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:42:23 by plau              #+#    #+#             */
/*   Updated: 2023/03/22 14:55:29 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Start of the main function */
int	main(int ac, char **av, char **envp)
{
	t_prg	prg;

	setup_signal();
	shell_loop(&prg, envp);
	system("leaks -q minishell");
	(void)ac;
	(void)av;
}
