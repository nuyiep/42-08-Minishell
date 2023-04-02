/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 20:02:19 by plau              #+#    #+#             */
/*   Updated: 2023/03/31 21:55:29 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Make a copy of env and save into struct */
void	init_envp(t_prg *prg, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	prg->ls_envp = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (envp[++i])
		prg->ls_envp[i] = ft_strdup(envp[i]);
	prg->ls_envp[i] = NULL;
}

/* To initialize exp */
void	init_exp(t_prg *prg)
{
	prg->exp = malloc(sizeof(t_exp));
	prg->exp->pair = NULL;
	prg->exp->key = NULL;
	prg->exp->value = NULL;
}

/* To get the "PATH=" line from env */
void	get_path(t_prg *prg, char **envp)
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_substr(envp[i], 5, (ft_strlen(envp[i]) - 5));
			prg->path = ft_split(path, ':');
			free (path);
		}
		i++;
	}
}

/* Find number of path */
void	find_npath(t_prg *prg)
{
	int	k;

	k = 0;
	if (prg->path == NULL)
		return ;
	while (prg->path[k] != NULL)
		k++;
	prg->npath = k;
}

/* Init struct 2- with init exp - To comply with norminette */
void	init_with_exp(t_prg *prg)
{
	init_exp(prg);
	init_struct(prg);
}
