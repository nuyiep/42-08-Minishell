/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:33:39 by plau              #+#    #+#             */
/*   Updated: 2023/04/04 18:37:10 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* dup2(temp_fd, 0) - redirects the stdin of the current process */
/*						to temp_fd */
/* fd[0]- read */
/* fd[1]- write */
/* Check if the input is a path address */
/* If it is not, change to address */
int	ft_execute(t_prg *prg)
{
	char	*empty_str;

	empty_str = ft_strdup("");
	if ((ft_strncmp(prg->all_token[0], "/", 1) != 0))
	{
		get_path(prg, prg->ls_envp);
		find_npath(prg);
		cmd_access(prg, empty_str);
	}
	free(empty_str);
	execve(prg->all_token[0], prg->all_token, prg->ls_envp);
	error_nl(prg, prg->all_token[0]);
	return (1);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
		ft_printf("^C\n");
	else if (signum == SIGQUIT)
		ft_printf("^\\Quit: 3\n");
}

/* Just to execute one command */
int	single_command(t_prg *prg)
{
	int					status;
	struct sigaction	sa;

	if (fork() == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		ft_execute(prg);
	}
	else
	{
		sa.sa_handler = sig_handler;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = SA_RESTART;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
		waitpid(0, &status, WUNTRACED);
		if (WIFEXITED(status))
			g_error = (WEXITSTATUS(status));
		if (WIFSIGNALED(status))
			g_error = 130;
		waitpid(-1, NULL, 0);
	}
	return (0);
}
