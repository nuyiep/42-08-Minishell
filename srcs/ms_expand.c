/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:49:28 by nchoo             #+#    #+#             */
/*   Updated: 2023/03/11 00:45:56 by nchoo            ###   ########.fr       */
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
		if (!ft_strncmp(prg->ls_envp[i], key + 1, ft_strlen(key + 1)) \
		&& ft_strncmp(prg->ls_envp[ft_strlen(key + 1)], "=", 1))
		{
			pair = ft_split(prg->ls_envp[i],'=');

			ret = ft_strdup(pair[1]);
			ft_freesplit(pair);
			return (ret);
		}
		else
			ret = ft_strdup(" ");
	}
	return (ret);
}

char **expand_tokens(t_prg *prg)
{
	char **save_state;
	char *input;
	int i;
	
	save_state = prg->all_token;
	while (*prg->all_token)
	{
		input = *prg->all_token;
		i = 0;
		while (input[i])
		{
			if (input[i++] == '$')
			{
				*prg->all_token = expand(prg, input);
				// ft_printf("%s\n", input);
			}
		}
		prg->all_token++;
	}
	return(save_state);
}