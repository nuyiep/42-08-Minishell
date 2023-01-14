/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:15:00 by plau              #+#    #+#             */
/*   Updated: 2023/01/14 18:25:57 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Remove envp */
// if 
void	remove_update_envp(t_prg *prg)
{
	char	**new_envp;
	char	**output;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	output = NULL;
	while (prg->ls_envp[i] != NULL)
		i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	j = 0;
	while (k < i)
	{
		if (ft_strchr(prg->ls_envp[j], '=') != NULL)
			output = seperate_key_value(prg->ls_envp[j]);
		else
			output[0] = prg->ls_envp[j];
		if (ft_strcmp(prg->token.all_token[1], output[0]) != 0)
		{
			new_envp[j] = ft_strdup(prg->ls_envp[k]);
			j++;
		}
		k++;
	}
	ft_printf("j: %d\n", j);
	ft_printf("k: %d\n", k);
	new_envp[j] = 0;
	prg->ls_envp = new_envp;
}

/* Return 1 if token match with envp token */
int	match(t_prg *prg)
{
	int		i;
	char	**output;
	int		free;

	i = 0;
	free = 0;
	output = NULL;
	while (prg->ls_envp[i] != NULL)
	{
		if (ft_strchr(prg->ls_envp[i], '=') != NULL)
		{
			output = seperate_key_value(prg->ls_envp[i]);
			free = 1;
		}
		else
			output[0] = prg->ls_envp[i];
		if (ft_strcmp(prg->token.all_token[1], output[0]) == 0)
		{
			if (free == 1)
				ft_freesplit(output);
			return (1);
		}
		i++;
	}
	if (free == 1)
		ft_freesplit(output);
	return (0);
}

/* If unset (a- token[1]) is not empty */
/* Check if (a- token[1]) is same as envp's output[0] */
/* If yes, don't copy */
/* If no, copy to the new envp */
void	unset(t_prg *prg)
{
	int	i;

	i = 0;
	if (prg->token.all_token[1] != NULL)
	{
		if (match(prg) == 1)
			remove_update_envp(prg);
	}
}
