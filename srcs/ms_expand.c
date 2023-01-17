/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:49:28 by nchoo             #+#    #+#             */
/*   Updated: 2023/01/17 16:49:49 by nchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expand(t_prg *prg, char *key)
{
	int i = -1;
	char *ret;
	char **pair;
	
	ret = NULL;
	while (prg->ls_envp[++i])
	{
		pair = ft_split(prg->ls_envp[i],'=');
		if (!ft_strcmp(pair[0], key + 1))
		{
			ret = ft_strdup(pair[1]);
			break;
		}
		else
			ret = ft_strdup(" ");
	}
	ft_freesplit(pair);
	return (ret);
}