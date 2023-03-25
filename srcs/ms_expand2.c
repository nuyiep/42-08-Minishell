/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:58:26 by nchoo             #+#    #+#             */
/*   Updated: 2023/03/24 17:10:12 by nchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int find_pair(t_prg *prg, char *key)
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
			return (1)
		}
		else
		{
			prg->exp->key = ft_strdup(key);
			return (0);
		}
	}
}

/*
1.	Scans a string for $
2.	Checks to see if var is valid
3.	Calculates new size of string
4.	
*/
char *find_var(char *s)
{
	return (ft_strnstr(s, "$", ft_strlen(s)));
}

int vars_exist(char *s)
{
	while (find_var(s))
	{
		if (!is_var(s))
			return (0);
	}
	return (1);
}

void *replace_var(char *string, int i, t_prg *prg)
{
	char *new;
	char *old;
	char *var;
	
	while ()
	old = ft_substr(string, 0, i);
	var = get_var(string, i + 1);
	new = NULL;
	if (find_pair)
	{
		new = ft_strjoin(old, prg->key->value);
	}
	
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
				replace_var(*prg->all_token, i, prg);
			}
			i++;
		}
		prg->all_token++;
	}
	return(save_state);
}