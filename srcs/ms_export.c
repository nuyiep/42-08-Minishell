/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:08:26 by plau              #+#    #+#             */
/*   Updated: 2023/01/13 17:11:48 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Bubble sort */
void	bubble_sort(char **envp, int j, int k)
{
	char	*smaller;
	int		i;

	while (j < k - 1)
	{
		i = 0;
		while (i < k - 1)
		{
			if (ft_strcmp(envp[i], envp[i + 1]) > 0)
			{
				smaller = envp[i + 1];
				envp[i + 1] = envp[i];
				envp[i] = smaller;
			}
			else
				i++;
		}
		j++;
	}
}

/* Separate key=value */
char	**seperate_key_value(char *arg)
{
	char	**output;
	char	**arg_list;

	output = ft_calloc(3, sizeof(char **));
	arg_list = ft_split(arg, '=');
	output[0] = ft_strdup(arg_list[0]);
	output[1] = ft_strdup(arg + ft_strlen(output[0]) + 1);
	output[2] = 0;
	if (output[1][0] == '\0')
	{
		if (output[1])
			free(output[1]);
		if (arg[ft_strlen(arg) - 1] == '=')
			output[1] = ft_strdup("");
		else
			output[1] = 0;
	}
	ft_freesplit(arg_list);
	return (output);
}

void	seperate_print(int k, char **output, char **new_envp)
{
	int	j;

	j = 0;
	while (j < k)
	{
		output = seperate_key_value(new_envp[j]);
		ft_printf("declare -x %s", output[0]);
		if (output[1] != NULL)
			ft_printf("=\"%s\"\n", output[1]);
		else
			ft_printf("\n");
		ft_freesplit(output);
		j++;
	}
	ft_freesplit(new_envp);
}

/* print sorted env with declare -x suffix */
// Ok- Remember to duplicate envp before sorting
// Ok- Remember to add "" to value
void	declare_x(t_prg *prg)
{
	int		j;
	int		k;
	int		h;
	char	**new_envp;
	char	**output;

	j = 0;
	k = 0;
	h = 0;
	output = NULL;
	while (prg->ls_envp[k] != NULL)
		k++;
	new_envp = malloc(sizeof(char *) * (k + 1));
	while (prg->ls_envp[h] != NULL)
	{
		new_envp[h] = ft_strdup(prg->ls_envp[h]);
		h++;
	}
	new_envp[h] = NULL;
	bubble_sort(new_envp, j, k);
	seperate_print(k, output, new_envp);
}

/* If export is called without any arguments, print env with declare -x */
/* Otherwise, add the given variables to the end of env variables */
// export a -> No value
// export a= -> Value is empty string
void	export(t_prg *prg)
{
	char	**pair;
	int		i;

	if (prg->token.all_token[1] == NULL)
		declare_x(prg);
	else
	{
		i = 0;
		while (prg->token.all_token[++i])
		{
			pair = seperate_key_value(prg->token.all_token[i]);
			if (key_exist(prg, pair[0]))
				update_key(prg, prg->token.all_token[i], pair[0]);
			else
			{
				if (pair[1] == NULL)
					add_key(prg, pair[0]);
				else
					add_key(prg, prg->token.all_token[i]);
			}
			ft_freesplit(pair);
		}
	}
}
