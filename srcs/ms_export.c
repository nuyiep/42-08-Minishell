/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:39:53 by plau              #+#    #+#             */
/*   Updated: 2023/01/10 19:54:11 by plau             ###   ########.fr       */
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

// export BBTEAM=Giants
// env $BBTEAM (will print Giants)
// exit

/* If export is called without any arguments, print env with declare -x */
/* Otherwise, add the given variables to the env variables */
void	export(t_prg *prg, char **envp)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	if (prg->token.all_token[1] == NULL)
		declare_x(prg, envp);
	else
	{
		if (ft_strcmp(prg->token.all_token[1], "=") == 0)
			error_nl(prg, "export = is not a valid identifier");
		while (prg->ls_envp[i] != NULL)
			i++;
		prg->ls_envp[i] = malloc(sizeof(char) * ft_strlen(prg->token.all_token[1]) + 1);
		prg->ls_envp[i] = prg->token.all_token[1];
		// while (prg->token.all_token[1][j] != '\0')
		// {
		// 	prg->ls_envp[i][k] = prg->token.all_token[1][j]; 
		// 	j++;
		// 	k++;
		// 	if (prg->ls_envp[i][k] == '=')
		// 	{
		// 		prg->ls_envp[i][k++] == '"';
		// 	}
		// }
	}
}
