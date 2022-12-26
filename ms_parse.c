/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:48:49 by plau              #+#    #+#             */
/*   Updated: 2022/12/26 21:42:11 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Check for heredoc- >> */
/* Check  for \n - end */
void	parse_checker(t_prg *prg, int i)
{
	if (prg->input[i] == '>')
	{
		if (prg->input[i + 1] == '>')
			prg->hed = 1;		
	}
	if (prg->input[i] == '\n')
		return ;
		
}

/* Eg. cat < test.txt | grep -n public > test2.txt &  */
/*     test.txt */
/* ls -l */
/* 1. cat - get_command() */
/* 2. <    */
/* 3. pipe  */
/* 4.  */ 
void	get_command(t_prg *prg, int count)
{
	int	i;
	
	i = 0;
	while (prg->input[i] != '\0')
	{
		while (prg->input[i] == ' ' || prg->input[i] == '\t')
			i++;
		parse_checker(prg, i);
		
	}
}

