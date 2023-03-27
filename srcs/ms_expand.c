/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:49:28 by nchoo             #+#    #+#             */
/*   Updated: 2023/03/27 18:13:00 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_new_size(t_prg *prg, char *old)
{
	int	size_key;
	int	size_value;
	int	size_old;
	int	new_size;

	size_old = ft_strlen(old);
	size_key = ft_strlen(prg->exp->key) + 1;
	size_value = ft_strlen(prg->exp->value);
	new_size = size_old - size_key + size_value + 1;
	return (new_size);
}

char	*create_string(t_prg *prg, char *old, int size, int var)
{
	char	*new_token;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	new_token = malloc(sizeof(char) * (size));
	while (i < size)
	{
		while (i < var)
			new_token[i++] = old[k++];
		while (prg->exp->value[j])
			new_token[i++] = prg->exp->value[j++];
		if (old[k + ft_strlen(prg->exp->key) + 1])
			new_token[i] = old[ft_strlen(prg->exp->key) + 1 + k++];
		i++;
	}
	new_token[i - 1] = '\0';
	return (new_token);
}

char	*create_new_token(t_prg *prg, char *old, int *i)
{
	char	*new_token;
	char	*var;
	int		var_pos;
	int		size;

	var_pos = 0;
	var = get_var(old, *i + 1);
	var_pos = 0;
	*i = -1;
	get_value(prg, var);
	free(var);
	var = 0;
	size = find_new_size(prg, old);
	if (*prg->exp->key)
		var_pos = find_var(old, prg->exp->key);
	new_token = create_string(prg, old, size, var_pos);
	free(old);
	return (new_token);
}

char	**expand_tokens(t_prg *prg)
{
	char	**save_state;
	char	*token;
	int		i;

	save_state = prg->all_token;
	while (*prg->all_token)
	{
		token = *prg->all_token;
		i = -1;
		while (token[++i])
		{
			if (token[i] == '\'')
			{
				if (has_pair_first(token))
					break ;
			}
			if (token[i] == '$')
			{
				*prg->all_token = create_new_token(prg, *prg->all_token, &i);
				token = *prg->all_token;
			}
		}
		prg->all_token++;
	}
	return (save_state);
}
