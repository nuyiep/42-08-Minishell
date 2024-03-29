/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:44:45 by plau              #+#    #+#             */
/*   Updated: 2023/04/04 18:37:17 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Wait function for heredoc */
/* 130 is the exit code after e.g. grep/cat an empty command */
void	wait_heredoc(void)
{
	int	status;

	waitpid(0, &status, WUNTRACED);
	if (WIFEXITED(status))
		g_error = (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		g_error = 130;
}

/* To execute heredoc */
/* E.g. pwd >> eof */
/* 		echo hi >> eof */
/*		exit >> eof */
/* Heredoc can handle expansion too	*/
void	execute_heredoc(t_prg *prg)
{
	int		pid;
	char	*empty_str;

	pid = 0;
	empty_str = ft_strdup("");
	pid = fork();
	free(prg->all_token[prg->heredoc_postion]);
	free(prg->all_token[prg->heredoc_postion + 1]);
	prg->all_token[prg->heredoc_postion] = NULL;
	if (pid == 0)
	{
		if (ft_strncmp(prg->all_token[0], "/", 1) != 0)
		{
			get_path(prg, prg->ls_envp);
			find_npath(prg);
			cmd_access(prg, empty_str);
		}
		execve(prg->all_token[0], prg->all_token, prg->ls_envp);
		error_nl(prg, prg->all_token[0]);
	}
	else
		wait_heredoc();
	free(empty_str);
}

/* Part of get_str function */
/* Separate it to comply with norminette */
void	get_str2(char *all_lines, t_prg *prg)
{
	if (ft_strcmp(prg->all_token[0], "cat") == 0)
		printf("%s", all_lines);
	else
		execute_heredoc(prg);
}

/* Printing out heredoc- until the delimiter is found */
void	get_str(char *delimiter, t_prg *prg)
{
	char	*each_line;
	char	*all_lines;

	all_lines = ft_strdup("");
	while (1)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		each_line = readline("> ");
		if (ft_strcmp(each_line, delimiter) == 0)
		{
			free(each_line);
			break ;
		}
		if (each_line == NULL)
			each_line = ft_strdup("");
		else
			each_line = ft_strjoin_free(each_line, "\n");
		all_lines = ft_strjoin_free(all_lines, each_line);
		free(each_line);
	}
	get_str2(all_lines, prg);
	free(all_lines);
}

/* Main function for heredoc */
/* if << is not found then return 1 */
/* E.g. cat << eof */
int	ms_heredoc(t_prg *prg, char **av)
{
	char	*delimiter;

	if (prg->heredoc == 0)
		return (1);
	delimiter = av[prg->heredoc_postion + 1];
	get_str(delimiter, prg);
	return (0);
}
