/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:45:41 by plau              #+#    #+#             */
/*   Updated: 2023/01/10 14:20:13 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* rl_on_new_line- moves the cursor position to the beginning of the line */
/* 					and resets the line buffer */
/* rl_replace_line- replace the current line of input with a new string */
/* 					first argument is the new string */
/*					second argument is the length of the new string */
/* rl_redisplay- displays the current line of input in terminal	*/				
void	sigint_handler(int sig)
{
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

/* Tcgetattr- Retrieve the current terminal attributes */
/*				and store them in controlc */
/* Tcsetattr- TCSANOW- change shall occur immediately */
/* Ignores SIGQUIT (ctrl \) - to not exit */
void	setup_signal(void)
{
	struct termios	controlc;

	tcgetattr(STDIN_FILENO, &controlc);
	controlc.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &controlc);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
