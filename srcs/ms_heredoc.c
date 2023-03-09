/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:44:45 by plau              #+#    #+#             */
/*   Updated: 2023/03/09 12:17:02 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_str(t_prg *prg, char *delimiter)
{
	char	*each_line;
	char	*all_lines;

	all_lines = ft_strdup("");
	while (1)
	{
		each_line = readline("> ");
		if (ft_strcmp(each_line, delimiter) == 0)
		{
			// free(all_lines);
			break ;
		}
		each_line = ft_strjoin_free(each_line, "\n");
		//process_str(prg, each_line);- for expansion
		all_lines = ft_strjoin_free(all_lines, each_line);
		free(each_line);
	}
	return (all_lines);
	(void)prg;
}

/* Main function for heredoc */
/* if << is not found at 2nd token then return 0 */
/* if not heredoc then return 0 */
/* codes written based on the structure: */
/* cat << eof */
/* $heredoc> hello */
/* read end = f[0] */
/* write end = fd[1] */
int	ms_heredoc(t_prg *prg, char **av, char **envp)
{
	char	*heredoc;
	char	*delimiter;
	int		fd[2];

	if (ft_strcmp("<<", prg->all_token[1]) != 0)
		return (0);
	delimiter = prg->all_token[2];
	heredoc = NULL;
	if (pipe(fd) == -1)
		error_nl(prg, "Pipe");
	heredoc = get_str(prg, delimiter);
	//write(fd[1], heredoc, ft_strlen(heredoc));
	printf("%s", heredoc);
	close(fd[1]);
	free(heredoc);
	return (fd[0]);
	(void)av;
	(void)envp;
}
