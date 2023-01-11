/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:08:26 by plau              #+#    #+#             */
/*   Updated: 2023/01/11 18:37:23 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Bubble sort */
void	bubble_sort(t_prg *prg, int j, int k, int i)
{
	char	*smaller;

	while (j < k - 1)
	{
		i = 0;
		while (i < k - 1)
		{
			if (ft_strcmp(prg->ls_envp[i], prg->ls_envp[i + 1]) > 0)
			{
				smaller = prg->ls_envp[i + 1];
				prg->ls_envp[i + 1] = prg->ls_envp[i];
				prg->ls_envp[i] = smaller;
			}
			else
				i++;
		}
		j++;
	}
}

/* print sorted env with declare -x suffix */
void	declare_x(t_prg *prg, char **envp)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (prg->ls_envp[k] != NULL)
		k++;
	bubble_sort(prg, j, k, i);
	i = 0;
	while (i < k)
	{
		ft_printf("declare -x %s\n", prg->ls_envp[i]);
		i++;
	}
	(void)envp;
}

char	**seperate_key_value(char *arg)
{
	char	**output;
	char	**arg_list;

	output = ft_calloc(3, sizeof(char *));
	arg_list = ft_split(arg, '=');
	output[0] = arg_list[0];
	output[1] = ft_strdup(arg + ft_strlen(output[0]) + 1);
	output[2] = 0;
	if (output[1][0] == '\0')
	{
		if (arg[ft_strlen(arg) - 1] == '=')
		{
			ft_printf("Empty string\n");
			output[1] = "";
		}
		else
		{
			ft_printf("No value\n");
			output[1] = 0;
		}
	}
	return (output);
}

/* If export is called without any arguments, print env with declare -x */
/* Otherwise, add the given variables to the end of env variables */

// export a -> No value
// export a= -> Value is empty string
void	export(t_prg *prg, char **envp)
{
	char	**pair; //[key, value]

	if (prg->token.all_token[1] == NULL)
		declare_x(prg, envp);
	else
	{
		pair = seperate_key_value(prg->token.all_token[1]);
		ft_printf("|%s|\n", pair[0]);
		ft_printf("|%s|\n", pair[1]);
		ft_printf("|%s|\n", pair[2]);
		/*
		
			if (already exist)
				update;
			else
			{
				if (value == 0)
					put key only;
				else
					put key + value;
			}
		*/
	}
}
