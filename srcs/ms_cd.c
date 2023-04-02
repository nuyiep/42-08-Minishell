/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:31:22 by plau              #+#    #+#             */
/*   Updated: 2023/03/31 21:46:14 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* To get the HOME= address */
char	*get_home_path(char **envp)
{
	int		i;
	char	*home_path;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "HOME=", 5) == 0)
			home_path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
		i++;
	}
	return (home_path);
}

/* Absolute path: cd /home/plau/stuff 	*/
/* 				  always start with / 	*/
/* Relative path: cd stuff 				*/
/* 				  ../.. 				*/
/* Do cd first - go back to root 	 	*/
void	cd(t_prg *prg, char **envp)
{
	char	*newdir;

	if (prg->all_token[1] == NULL)
	{
		newdir = get_home_path(envp);
		chdir(newdir);
		free(newdir);
	}
	else if (prg->all_token[1] != NULL)
		chdir(prg->all_token[1]);
}
