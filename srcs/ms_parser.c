/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:16:07 by nchoo             #+#    #+#             */
/*   Updated: 2023/03/23 10:36:53 by nchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void remove_quote(char* str) 
{
    size_t len = strlen(str);
    if (len >= 2 && str[0] == '"' && str[len - 1] == '"') 
	{
        str[len - 1] = '\0';
        memmove(str, str + 1, len - 1);
    } 
	else if (len >= 2 && str[0] == '\'' && str[len - 1] == '\'') 
	{
        str[len - 1] = '\0';
        memmove(str, str + 1, len - 1);
    }
}

char **remove_quotes(t_prg *prg)
{
	char **save_state;
	
	save_state = prg->all_token;
	while (*prg->all_token)
	{
		remove_quote(*prg->all_token);
		prg->all_token++;
	}
	return (save_state);
}