/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:49:28 by nchoo             #+#    #+#             */
/*   Updated: 2023/03/25 15:07:53 by nchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void find_pair(t_prg *prg, char *key)
{
	int i = -1;
	char ***pair;
	char **save_state;
	
	if (!ft_strncmp(key, "?", 1))
	{
		prg->exp->key = ft_strdup("?");
		prg->exp->value = ft_itoa(exit_code);
		return ;
	}
	while (prg->ls_envp[++i])
	{
		if (!ft_strncmp(prg->ls_envp[i], key, ft_strlen(key)) \
		&& (prg->ls_envp[i][ft_strlen(key)] == '='))
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
			break ;
		}
		else
		{
			prg->exp->key = ft_strdup(key);
			if (prg->exp->value) {
				free(prg->exp->value);
				prg->exp->value = ft_strdup(" ");
			}
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
	// ft_printf("old: %d\n", size_old);
	size_key = ft_strlen(prg->exp->key) + 1;
	// ft_printf("key: %d\n", size_key);
	size_value = ft_strlen(prg->exp->value);
	// ft_printf("value: %d\n", size_value);
	new_size = size_old - size_key + size_value + 1;
	// ft_printf("size: %d\n", new_size);
	return (new_size);
}

static int find_var_in_token(char *token, char *var)
{
	int	i;
	int j;

	i = -1;
	if (!var || var[0] == 0)
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
	var = 0;
	key = prg->exp->key;
	// ft_printf("key: %s\n", key);
	value = prg->exp->value;
	// ft_printf("value: %s\n", value);
	size = find_new_size(prg, old);
	new_token = malloc(sizeof(char) * (size));
	if (key)
		var = find_var_in_token(old, key);
	while (i < size)
	{
		while (i < var)
			new_token[i++] = old[k++];
		while (value[j])
			new_token[i++] = value[j++];
		if (old[k + ft_strlen(key) + 1])
			new_token[i] = old[ft_strlen(key) + 1 + k++];
		i++;
	}
	new_token[i - 1] = '\0';
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
			if (token[i] == '\'')
			{
				if (has_pair_first(token, prg))
					break ;
			}
			if (token[i] == '$')
			{
				var = get_var(token, i + 1);
				find_pair(prg, var);
				free(var);
				*prg->all_token = create_new_token(prg, *prg->all_token);
				// ft_printf("%s\n", *prg->all_token);
			}
			i++;
		}
		prg->all_token++;
	}
	return(save_state);
}