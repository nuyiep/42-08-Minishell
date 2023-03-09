/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:42:23 by plau              #+#    #+#             */
/*   Updated: 2023/03/09 12:21:13 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_prg	prg;

	init_struct(&prg, av, ac, envp);
	setup_signal();
	shell_loop(&prg, envp, av);
	// system("leaks -q minishell");
}
