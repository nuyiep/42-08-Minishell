/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:44:45 by plau              #+#    #+#             */
/*   Updated: 2023/03/21 17:55:16 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Printing out heredoc- until the delimiter is found */
void	get_str(char *delimiter)
{
	char	*each_line;
	char	*all_lines;

	all_lines = ft_strdup("");
	while (1)
	{
		each_line = readline("> ");
		if (ft_strcmp(each_line, delimiter) == 0)
		{
			free(each_line);
			break ;
		}
		each_line = ft_strjoin_free(each_line, "\n");
		all_lines = ft_strjoin_free(all_lines, each_line);
		free(each_line);
	}
	printf("%s", all_lines);
	free(all_lines);
}

/* Main function for heredoc */
/* if << is not found then return 1 */
/* E.g. cat << eof */
int	ms_heredoc(t_prg *prg)
{
	char	*delimiter;

	if (prg->heredoc == 0)
		return (1);
	delimiter = prg->all_token[prg->heredoc_postion + 1];
	get_str(delimiter);
	return (0);
}
