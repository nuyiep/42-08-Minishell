/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:49:28 by nchoo             #+#    #+#             */
/*   Updated: 2023/03/11 18:33:21 by nchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void find_pair(t_prg *prg, char *key)
{
	int i = -1;
	char ***pair;
	char **save_state;
	
	while (prg->ls_envp[++i])
	{
		if (!ft_strncmp(prg->ls_envp[i], key + 1, ft_strlen(key + 1)) \
		&& ft_strncmp(prg->ls_envp[ft_strlen(key + 1)], "=", 1))
		{
			save_state = prg->exp->pair;
			pair = &prg->exp->pair;
			pair[0] = ft_split(prg->ls_envp[i],'=');

			prg->exp->key = ft_strdup(pair[0][0]);
			if (pair[0][1])
				prg->exp->value = ft_strdup(pair[0][1]);
			prg->exp->pair = save_state;
		}
	}
}

/*
static int find_new_size(t_prg *prg, char *old)
{
	int	size_key;
	int	size_value;
	int size_old;
	int new_size;
	
	size_old = ft_strlen(old);
	ft_printf("old: %d\n", size_old);
	size_key = ft_strlen(prg->exp->key);
	ft_printf("key: %d\n", size_key);
	size_value = ft_strlen(prg->exp->value);
	ft_printf("value: %d\n", size_value);
	new_size = size_old - size_key + size_value + 1;
	ft_printf("size: %d\n", new_size);
	return (new_size);
}

static char *create_new_token(t_prg *prg, char *old)
{
	char *new_token;
	char *key;
	char *value;
	int i = -1;
	int j = 0;
	
	key = prg->exp->key;
	value = prg->exp->value;
	new_token = malloc(sizeof(char) * (find_new_size(prg, old)));
	while (value[++i])
		new_token[i] = value[i];
	j += i;
	while (old[j])
		new_token[i++] = old[j++];
	new_token[i] = '\0';
	return (new_token);
}
 */

char **expand_tokens(t_prg *prg)
{
	char **save_state;
	char *token;
	int i;
	
	free_exp(prg);
	save_state = prg->all_token;
	while (*prg->all_token)
	{
		token = *prg->all_token;
		i = 0;
		while (token[i])
		{
			if (token[i++] == '$')
			{
				find_pair(prg, token);
				*prg->all_token = ft_strdup(prg->exp->value);
				// ft_printf("%s\n", input);
			}
		}
		prg->all_token++;
	}
	return(save_state);
}