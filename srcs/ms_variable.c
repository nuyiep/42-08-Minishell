/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_variable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 17:17:47 by nchoo             #+#    #+#             */
/*   Updated: 2023/03/29 21:57:23 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_value(t_prg *prg, char *key, int i)
{
	char	**save_state;
	char	***pair;

	save_state = prg->exp->pair;
	pair = &prg->exp->pair;
	pair[0] = ft_split(prg->ls_envp[i], '=');
	if (prg->exp->key)
		free(prg->exp->key);
	prg->exp->key = ft_strdup(key);
	if (pair[0][1])
	{
		if (prg->exp->value)
		{
			free(prg->exp->value);
			prg->exp->value = ft_strdup(pair[0][1]);
		}
	}
	prg->exp->pair = save_state;
}

void	assign_empty(t_prg *prg, char *key)
{
	prg->exp->key = ft_strdup(key);
	if (prg->exp->value)
	{
		free(prg->exp->value);
		prg->exp->value = ft_strdup(" ");
	}
}

int	find_var(char *token, char *var)
{
	int	i;
	int	j;

	i = -1;
	if (!var || var[0] == 0)
		return (0);
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

char	*get_var(char *token, int i)
{
	char	*var;
	int		j;

	j = 0;
	if (token[i] == '?')
	{
		var = ft_strdup("?");
		return (var);
	}
	while (token[i] && token[i] != ' ' \
	&& token[i] != '\'' && token[i] != '\"')
	{
		j++;
		i++;
	}
	var = malloc(sizeof(char) * (j + 1));
	i -= j;
	j = 0;
	while (token[i] && token[i] != ' ' \
	&& token[i] != '\'' && token[i] != '\"' \
	&& ft_isalpha(token[i]))
		var[j++] = token[i++];
	var[j] = '\0';
	return (var);
}

void	get_value(t_prg *prg, char *key)
{
	int	i;

	i = -1;
	if (is_question(prg, key))
		return ;
	while (prg->ls_envp[++i])
	{
		if (has_value(prg, key, i))
		{
			assign_value(prg, key, i);
			break ;
		}
		else
			assign_empty(prg, key);
	}
}
