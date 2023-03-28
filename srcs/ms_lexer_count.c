/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:48:20 by nchoo             #+#    #+#             */
/*   Updated: 2023/03/28 17:51:53 by nchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_first_count(char *s, int *count, int *check)
{
	if (*s)
	{
		if ((*s == '\'') || (*s == '\"'))
		{
			if (has_pair_first(s) != 0)
			{
				*count += 1;
				*check = 0;
				s += has_pair_first(s);
			}
		}	
	}
	return (s);
}

void	increment_count_zero_check(int *count, int *check)
{
	*count += 1;
	*check = 0;
}

char	*do_count(char *s, int *count, int *check)
{
	if (has_operators(*s, ">|<"))
	{
		increment_count_zero_check(count, check);
		if (*(s + 1) && ((*s == '>' && *(s + 1) == '>') \
		|| (*s == '<' && *(s + 1) == '<')))
			s++;
	}
	if (*check && !(has_operators(*s, ">|< ")))
		increment_count_zero_check(count, check);
	else if (!*check && (has_operators(*s, ">|< ")))
	{
		*check = 1;
		if ((*(s + 1) == '\'') | (*(s + 1) == '\"'))
		{
			if (has_pair(s) != 0)
			{
				increment_count_zero_check(count, check);
				s += has_pair(s);
			}
		}
	}
	return (s);
}

int	count_tab(char *s)
{
	int	check;
	int	count;

	count = 0;
	check = 1;
	s = check_first_count(s, &count, &check);
	while (*s)
	{
		s = do_count(s, &count, &check);
		s++;
	}
	return (count);
}
