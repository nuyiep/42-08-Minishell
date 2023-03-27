/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:00:46 by nchoo             #+#    #+#             */
/*   Updated: 2023/03/27 17:05:16 by nchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_tab(char *s)
{
	int check;
	int count;
	int i;
	
	i = 0;
	count = 0;
	check = 1;
	if (*s)
	{
		if ((*s == '\'') || (*s == '\"'))
		{
			i = has_pair_first(s);
			if (i != 0)
			{
				count++;
				check = 0;
				s += i;
			}
		}		
	}
	while (*s)
	{
		if (check && !(has_operators(*s, ">|< ")))
		{
			count++;
			check = 0;
		}
		else if (!check && (has_operators(*s, ">|< ")))
		{
			check = 1;
			if ((*(s + 1) == '\'') | (*(s + 1) == '\"')) 
			{
				if (has_pair(s) != 0)
				{
					count++;
					s += has_pair(s);
					check = 0;
				}
			}
		}
		if (has_operators(*s, ">|<")) {
			count++;
			check = 1;
		}
		s++;
	}
	return (count);	
}

char	*copy_token(const char *s)
{
	char *p;
	int i;

	i = 0;
	while (s[i] && !(has_operators(s[i], ">|< ")))
		i++;
	p = ft_strndup(s, i);
	return (p);
}

char	*copy_operator(const char *s)
{
	char *p;
	int i;

	i = 0;
	while (s[i] && (has_operators(s[i], ">|<")))
		i++;
	p = ft_strndup(s, i);
	return (p);
}

char **split_token(t_prg *prg)
{
	char	**tab;
	int		count;
	int		check;
	char	*s;
	int		i;

	s = prg->input;
	if (!s)
		return (NULL);
	check = 1;
	count = count_tab((char *)s);
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	if (*s)
	{
		if ((*s == '\'') || (*s == '\"'))
		{
			i = has_pair_first(s);
			if (i != 0)
			{
				*tab++ = ft_strndup(s, i);
				s += i;
				check = 0;
			}
		}		
	}
	while (*s)
	{
		if (check && !(has_operators(*s, ">|< ")))
		{
			*tab++ = copy_token(s);
			check = 0;
		}
		else if (!check && (has_operators(*s, ">|< ")))
		{
			check = 1;
			if ((*(s + 1) == '\'') || (*(s + 1) == '\"'))
			{
				i = has_pair(s);
				if (i != 0)
				{
					*tab++ = ft_strndup(s + 1, i);
					s += i;
					check = 0;
				}
			}
		}
		if (has_operators(*s, ">|<"))
		{
			*tab++ = copy_operator(s);
			check = 1;
		}
		s++;
	}
	*tab = 0;
	return (tab - count);
}
