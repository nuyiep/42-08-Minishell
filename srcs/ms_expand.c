/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:49:28 by nchoo             #+#    #+#             */
/*   Updated: 2023/03/13 21:10:46 by nchoo            ###   ########.fr       */
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
		if (!ft_strncmp(prg->ls_envp[i], key, ft_strlen(key)) \
		&& ft_strncmp(prg->ls_envp[ft_strlen(key)], "=", 1))
		{
			save_state = prg->exp->pair;
			pair = &prg->exp->pair;
			pair[0] = ft_split(prg->ls_envp[i],'=');

			if (prg->exp->key)
				free(prg->exp->key);
			prg->exp->key = ft_strdup(key);
			if (pair[0][1])
			{
				if (prg->exp->value)
					free(prg->exp->value);
				prg->exp->value = ft_strdup(pair[0][1]);
			}
			prg->exp->pair = save_state;
		}
	}
}

static int find_new_size(t_prg *prg, char *old)
{
	int	size_key;
	int	size_value;
	int size_old;
	int new_size;
	
	size_old = ft_strlen(old);
	size_key = ft_strlen(prg->exp->key) + 1;
	size_value = ft_strlen(prg->exp->value);
	new_size = size_old - size_key + size_value + 1;
	return (new_size);
}

static int find_var_in_token(char *token, char *var)
{
	int	i;
	int j;

	i = -1;
	if (var[0] == 0)
		return(0);
	while (token[++i])
	{
		j = 0;
		while (token[i + j] && var[j] \
			&& token[i + j] == var[j])
			j++;
		if (!var[j])
			return (i - 1);
	}
	return (0);
}

static char *create_new_token(t_prg *prg, char *old)
{
	char *new_token;
	char *key;
	char *value;
	int i;
	int j;
	int k;
	int var;
	int size;
	
	i = 0;
	j = 0;
	k = 0;
	key = prg->exp->key;
	value = prg->exp->value;
	size = find_new_size(prg, old);
	new_token = malloc(sizeof(char) * (size));
	var = find_var_in_token(old, key);
	while (i < size)
	{
		while (i < var)
			new_token[i++] = old[k++];
		while (value[j])
			new_token[i++] = value[j++];
		if (old[k])
			new_token[i++] = old[j + k++];
	}
	return (new_token);
}


char **expand_tokens(t_prg *prg)
{
	char **save_state;
	char *token;
	char *var;
	int i;
	
	free_exp(prg, 1);
	save_state = prg->all_token;
	while (*prg->all_token)
	{
		token = *prg->all_token;
		i = 0;
		while (token[i])
		{
			if (token[i] == '$')
			{
				var = get_var(token, i + 1);
				find_pair(prg, var);
				free(var);
				*prg->all_token = create_new_token(prg, token);
				// *prg->all_token = ft_strdup(prg->exp->value);
				// ft_printf("%s\n", input);
			}
			i++;
		}
		prg->all_token++;
	}
	return(save_state);
}