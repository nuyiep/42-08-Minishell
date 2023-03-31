/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:16:07 by nchoo             #+#    #+#             */
/*   Updated: 2023/03/31 18:46:14 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Simple function to remove quotes from 
	the front and back of a string
*/
// void	remove_quote(char *str)
// {
// 	int	len;

// 	len = ft_strlen(str);
// 	if (len >= 2 && str[0] == '"' && str[len - 1] == '"')
// 	{
// 		str[len - 1] = '\0';
// 		ft_memmove(str, str + 1, len - 1);
// 	}
// 	else if (len >= 2 && str[0] == '\'' && str[len - 1] == '\'')
// 	{
// 		str[len - 1] = '\0';
// 		ft_memmove(str, str + 1, len - 1);
// 	}
// }

void	remove_quote(char *str)
{
	char	*buffer;
	char	*src;
	char	*dst;
	size_t	dst_size;

	buffer = malloc(sizeof(char) * (ft_strlen(str) + 1));
	src = str;
	dst = buffer;
	dst_size = ft_strlen(str);
	while (*src && dst_size >= 1)
	{
		if (*src != '\"' && *src != '\'')
		{
			*dst++ = *src++;
			dst_size--;
		}
		else
			src++;
	}
	*dst = '\0';
	ft_strlcpy(str, buffer, ft_strlen(str) + 1);
	free(buffer);
}

/*
	Loops through all tokens and runs the function
	to remove quotes from the front and back of
	the strings
*/
char	**remove_all_quotes(t_prg *prg)
{
	char	**save_state;

	save_state = prg->all_token;
	while (*prg->all_token)
	{
		remove_quote(*prg->all_token);
		prg->all_token++;
	}
	return (save_state);
}
