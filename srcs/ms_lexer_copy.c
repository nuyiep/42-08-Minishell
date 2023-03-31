/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:38:56 by nchoo             #+#    #+#             */
/*   Updated: 2023/03/31 01:36:26 by nchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_token(char *s, char ***tab, int *check)
{
	int		i;

	i = 0;
	while (s[i] && !(has_operators(s[i], ">|< ")))
		i++;
	**tab = ft_strndup(s, i);
	*tab += 1;
	*check = 0;
	return (s);
}

char	*copy_operator(char *s, char ***tab, int *check)
{
	int		i;

	i = 0;
	while (s[i] && (has_operators(s[i], ">|<")))
		i++;
	**tab = ft_strndup(s, i);
	*tab += 1;
	*check = 0;
	if (*(s + 1) && ((*s == '>' && *(s + 1) == '>') \
	|| (*s == '<' && *(s + 1) == '<')))
		s++;
	return (s);
}

char	*copy_quoted(char *s, char ***tab, int *check)
{
	if (has_pair(s) != 0)
	{
		**tab = ft_strndup(s + 1, has_pair(s));
		*tab += 1;
		s += has_pair(s);
		*check = 0;
	}
	return (s);
}

char	*check_first_quote(char *s, char ***tab, int *check)
{
	if (*s)
	{
		if ((*s == '\'') || (*s == '\"'))
		{
			if (has_pair_first(s, 0) != 0)
			{
				**tab = ft_strndup(s, has_pair_first(s, 0));
				*tab += 1;
				s += has_pair_first(s, 0);
				*check = 0;
			}
		}		
	}
	return (s);
}
