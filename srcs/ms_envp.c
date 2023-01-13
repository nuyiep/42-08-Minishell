/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 20:35:47 by plau              #+#    #+#             */
/*   Updated: 2023/01/13 16:55:57 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* To get the "PATH=" line from envp */
/* To calculate the number of path */
/* Calculate the number of env lines */
void	get_path(t_prg *prg, char **envp)
{
	char	*path;
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
			prg->envp = ft_split(path, ':');
			free (path);
		}
		i++;
	}
	while (prg->envp[prg->npath] != NULL)
		prg->npath++;
	while (prg->ls_envp[prg->n_env] != NULL)
		prg->n_env++;
}

/* To get the PATH address */
void	get_address_one(t_prg *prg)
{
	int		i;
	char	*temp;
	char	*cmd;

	i = 0;
	while (i < prg->npath)
	{
		temp = ft_strjoin(prg->envp[i], "/");
		cmd = ft_strjoin(temp, prg->token.cmd1);
		i++;
		if (access(cmd, F_OK) == 0)
		{
			prg->cmdpath1 = cmd;
			free(temp);
			return ;
		}
		free(cmd);
		free(temp);
	}
}

/* Check whether key has value */
int	got_value(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

/* To print the list of env */
void	env(t_prg *prg)
{
	int	i;

	i = 0;
	while (prg->ls_envp[i] != NULL)
	{
		if (got_value(prg->ls_envp[i]))
			ft_printf("%s\n", prg->ls_envp[i]);
		i++;
	}
}
