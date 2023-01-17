/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 16:57:15 by plau              #+#    #+#             */
/*   Updated: 2023/01/17 16:05:19 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* PWD */
void	pwd(t_prg *prg)
{
	char	*pwd;

	if (prg->all_token[1] != NULL)
		ft_printf("Too many arguments\n");
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		error_nl(prg, "Pwd failed");
	ft_printf("%s\n", pwd);
	free(pwd);
}
