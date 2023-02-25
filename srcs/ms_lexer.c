/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:00:46 by nchoo             #+#    #+#             */
/*   Updated: 2023/02/25 16:31:12 by nchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# DEFINE OPERATORS "<<>><>|"

echo "hi    hello" | grep -n 'el' > outfile

int	count_words(t_prg prg)
{
	int i;
	int t;
	int count;
	
	i = 0;
	t = 1;
	while (prg->input[i])
	{
		
	}	
}

char **split_token(t_prg prg, char *s)
{
	
}