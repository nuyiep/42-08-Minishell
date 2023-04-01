/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_access.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:55:33 by plau              #+#    #+#             */
/*   Updated: 2023/04/01 18:37:28 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Check for cmd access part 2 - To comply with norminette */
char	*cmd_access2(t_prg *prg, char *temp, char *av_zero)
{
	if (access(temp, X_OK) == 0)
	{
		if (prg->no_pipes == 0)
		{
			prg->all_token[0] = temp;
			return (prg->all_token[0]);
		}
		else
		{
			av_zero = temp;
			return (av_zero);
		}
	}
	return (NULL);
}

/* Check for cmd access part 3 - To comply with norminette */
void	cmd_access3(t_prg *prg, char *av_zero)
{
	if (prg->no_pipes == 0)
	{
		g_error = 127;
		error_nl(prg, prg->all_token[0]);
	}
	else
	{
		g_error = 127;
		error_nl(prg, av_zero);
	}
}

/* Check cmd access */
char	*cmd_access(t_prg *prg, char *av_zero)
{
	int		j;
	char	*temp;
	char	*results;

	j = 0;
	while (j < prg->npath)
	{
		temp = ft_strjoin(prg->path[j], "/");
		if (prg->no_pipes == 0)
			temp = ft_strjoin_free(temp, prg->all_token[0]);
		else
			temp = ft_strjoin_free(temp, av_zero);
		results = cmd_access2(prg, temp, av_zero);
		if (results != NULL)
			return (results);
		j++;
		free(temp);
	}
	cmd_access3(prg, av_zero);
	return (NULL);
}
