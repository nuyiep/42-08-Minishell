/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 20:35:47 by plau              #+#    #+#             */
/*   Updated: 2022/12/24 18:02:22 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* To get the "PATH=" line from envp */
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
}

/* To get the PATH address */
void	get_address(t_prg *prg)
{
	int		i;
	char	*temp;
	char	*cmd;

	i = 0;
	while (i < prg->npath)
	{
		temp = ft_strjoin(prg->envp[i], "/");
		cmd = ft_strjoin(temp, prg->cmd[0]);
		i++;
		if (access(cmd, F_OK) == 0)
		{
			prg->cmdpath = cmd;
			free(temp);
			return ;
		}
		free(cmd);
		free(temp);
	}
}
