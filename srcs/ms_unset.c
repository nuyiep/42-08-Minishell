/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:15:00 by plau              #+#    #+#             */
/*   Updated: 2023/01/17 13:54:52 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Remove envp */
/* Copy envp to a temp (new_envp) */
/* free struct envp */
/* Copy temp to struct envp */
/* Free temp */
void	remove_update_envp(t_prg *prg)
{
	char	**new_envp;
	char	**output;
	int		i;
	int		j;
	int		k;
	int		free;

	i = 0;
	output = NULL;
	while (prg->ls_envp[i] != NULL)
		i++;
	new_envp = malloc(sizeof(char *) * i);
	k = 0;
	j = 0;
	while (prg->ls_envp[k] != NULL)
	{
		free = 0;
		if (ft_strchr(prg->ls_envp[k], '=') != NULL)
		{
			output = separate_key_value(prg->ls_envp[k]);
			free = 1;
		}
		else
			output[0] = prg->ls_envp[k];
		if (ft_strcmp(prg->token.all_token[1], output[0]) != 0)
		{
			new_envp[j] = ft_strdup(prg->ls_envp[k]);
			j++;
		}
		if (free == 1)
			ft_freesplit(output);
		k++;
	}
	new_envp[j] = 0;
	ft_freesplit(prg->ls_envp);
	i = 0;
	prg->ls_envp = malloc(sizeof(char *) * (j + 1));
	while (new_envp[i] != 0)
	{
		prg->ls_envp[i] = ft_strdup(new_envp[i]);
		i++;
	}
	prg->ls_envp[i] = 0;
	ft_freesplit(new_envp);
}

/* Return 1 if token match with envp token */
/* Need this function to allocate correct memory */
int	match(t_prg *prg)
{
	int		i;
	char	**output;
	int		free;

	i = 0;
	output = NULL;
	while (prg->ls_envp[i] != NULL)
	{
		free = 0;
		if (ft_strchr(prg->ls_envp[i], '=') != NULL)
		{
			output = separate_key_value(prg->ls_envp[i]);
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
		if (free == 1)
			ft_freesplit(output);
		i++;
	}
	return (0);
}

/* If unset (a- token[1]) is not empty */
/* Check if (a- token[1]) is same as envp's output[0] */
/* If yes, don't copy */
/* If no, copy to the new envp */
void	unset(t_prg *prg)
{
	if (prg->token.all_token[1] != NULL)
	{
		if (match(prg) == 1)
			remove_update_envp(prg);
	}
}
