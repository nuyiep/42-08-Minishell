/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:00:46 by nchoo             #+#    #+#             */
/*   Updated: 2023/03/27 15:15:57 by nchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_tab(char *s, char c)
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
		if (check && !(*s == c))
		{
			count++;
			check = 0;
		}
		else if (!check && (*s == c))
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
		s++;
	}
	return (count);	
}

char	*copy_token(const char *s, char c)
{
	char *p;
	int i;

	i = 0;
	while (s[i] && !(s[i] == c))
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
	count = count_tab((char *)s, 32);
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
		if (check && !(*s == ' '))
		{
			*tab++ = copy_token(s, ' ');
			check = 0;
		}
		else if (!check && (*s == ' '))
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
		s++;
	}
	*tab = 0;
	return (tab - count);
}
