/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exporthelper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:40:25 by plau              #+#    #+#             */
/*   Updated: 2023/01/11 19:43:37 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Return 1 if key is found, else return 0
 */
int	key_exist(t_prg *prg, char *key)
{
	int		i;
	char	**split;

	i = 0;
	while (prg->ls_envp[i] != NULL)
	{
		split = ft_split(prg->ls_envp[i], '=');
		if (ft_strcmp(split[0], key) == 0)
		{
			ft_freesplit(split);	
			return (1);
		}
		ft_freesplit(split);
		i++;
	}
	return (0);
}

/**
 * Duplicate old envp
 * Copy old envp to new envp
 * Free old envp
 * Update new envp
 */
void	update_key(t_prg *prg, char *key)
{
	char	**new_envp;
	char	**split;
	int		i;
	int		j;

	i = 0;
	while (prg->ls_envp[i] != NULL)
		i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	j = 0;
	while (j < i)
	{
		split = ft_split(prg->ls_envp[j], '=');
		if (ft_strcmp(split[0], key) == 0)
			new_envp[j] = ft_strdup(prg->token.all_token[1]);
		else
			new_envp[j] = ft_strdup(prg->ls_envp[j]);
		j++;
		ft_freesplit(split);
	}
	new_envp[i] = 0;
	ft_freesplit(prg->ls_envp);
	prg->ls_envp = new_envp;
}

/**
 * declare -x a
 */
// void	add_without_eq(t_prg *prg, char *key)
// {
	
// }

/**
 * declare -x a="" 
 * declare -x key=value
 */
// void	add_with_eq(t_prg *prg, char *key)
// {

// }