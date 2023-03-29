/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:58:07 by nchoo             #+#    #+#             */
/*   Updated: 2023/03/29 15:11:55 by nchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	get_no_cmd(t_prg *prg)
{
	char	**tokens;
	int		no_cmd;

	no_cmd = 0;
	tokens = prg->all_token;
	while (*tokens)
	{
		if (!ft_strncmp(*tokens, "|", 1))
			no_cmd++;
		tokens++;
	}
	return (no_cmd + 1);
}

char	**get_cmd(t_prg *prg)
{
	char	**split;
	char	**tokens;
	int		i;
	int		no_cmd;

	i = 0;
	tokens = prg->all_token;
	no_cmd = get_no_cmd(prg);
	split = malloc(sizeof(char *) * (no_cmd + 1));
	while (i < no_cmd && *tokens)
	{
		split[i] = ft_strdup(*tokens++);
		while (*tokens && ft_strncmp(*tokens, "|", 1))
		{
			split[i] = ft_strjoin(split[i], " ");
			split[i] = ft_strjoin(split[i], *tokens);
			tokens++;
		}
		tokens++;
		i++;
	}
	split[i] = NULL;
	return (split);
}
