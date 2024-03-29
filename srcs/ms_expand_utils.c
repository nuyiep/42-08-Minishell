/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:29:40 by nchoo             #+#    #+#             */
/*   Updated: 2023/03/31 15:04:45 by nchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Checks whether the variable is "?"
*/
int	is_question(t_prg *prg, char *key)
{
	if (!ft_strncmp(key, "?", 1))
	{
		if (prg->exp->key)
			free(prg->exp->key);
		if (prg->exp->value)
			free(prg->exp->value);
		prg->exp->key = ft_strdup("?");
		prg->exp->value = ft_itoa(g_error);
		return (1);
	}
	return (0);
}

/*
	Checks whether the given key has an associated value
*/
int	has_value(t_prg *prg, char *key, int i)
{
	int	len;

	len = ft_strlen(key);
	if (!ft_strncmp(prg->ls_envp[i], key, len) \
	&& prg->ls_envp[i][len] == '=')
		return (1);
	return (0);
}
