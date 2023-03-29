/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:33:39 by plau              #+#    #+#             */
/*   Updated: 2023/03/29 21:25:19 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Check for cmd access part 2 */
char	*cmd_access2(t_prg *prg, char *temp, char *av_zero)
{
	if (access(temp, X_OK) == 0)
	{
		if (prg->no_pipes == 0)
		{
			prg->all_token[0] = temp;
			return (prg->all_token[0]);
		}
		else
		{
			av_zero = temp;
			return (av_zero);
		}
	}
	return (NULL);
}

void	cmd_access3(t_prg *prg, char *av_zero)
{
	if (prg->no_pipes == 0)
	{
		exit_code = 127;
		error_nl(prg, prg->all_token[0]);
	}
	else
	{
		exit_code = 127;
		error_nl(prg, av_zero);
	}
}

/* Check cmd access */
char	*cmd_access(t_prg *prg, char *av_zero)
{
	int		j;
	char	*temp;
	char	*results;

	j = 0;
	while (j < prg->npath)
	{
		temp = ft_strjoin(prg->path[j], "/");
		if (prg->no_pipes == 0)
			temp = ft_strjoin(temp, prg->all_token[0]);
		else
			temp = ft_strjoin(temp, av_zero);
		results = cmd_access2(prg, temp, av_zero);
		if (results != NULL)
			return (results);
		j++;
		free(temp);
	}
	cmd_access3(prg, av_zero);
	return (NULL);
}

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

/* Just to execute one command */
int	single_command(t_prg *prg)
{
	int	status;

	if (fork() == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		ft_execute(prg);
	}
	else
	{
		waitpid(0, &status, WUNTRACED);
		if (WIFEXITED(status))
			exit_code = (WEXITSTATUS(status));
		if (WIFSIGNALED(status))
			exit_code = 130;
		waitpid(-1, NULL, 0);
	}
	return (0);
}
