/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 16:57:15 by plau              #+#    #+#             */
/*   Updated: 2022/12/27 21:47:08 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* PWD */
void	pwd(t_prg *prg)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		exit_error("Pwd failed");
	if (ft_strcmp(prg->cmd[0], "pwd") == 0)
		ft_printf("%s\n", pwd);
	free(pwd);
}
