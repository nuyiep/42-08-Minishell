/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:58:07 by nchoo             #+#    #+#             */
/*   Updated: 2023/03/30 21:47:23 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void print_cmds(char **split)
// {
// 	int i;

// 	for (i = 0; split[i]; i++) {
// 		ft_printf("%s\n", split[i]);
// 	}
// }

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

char	*join_cmd(char *split, char *token)
{
	char	*temp;

	temp = split;
	split = ft_strjoin(split, " ");
	free(temp);
	temp = split;
	split = ft_strjoin(split, token);
	free(temp);
	return (split);
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
			split[i] = join_cmd(split[i], *tokens);
			tokens++;
		}
		tokens++;
		i++;
	}
	split[i] = NULL;
	return (split);
}
