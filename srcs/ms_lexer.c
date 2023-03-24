/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:00:46 by nchoo             #+#    #+#             */
/*   Updated: 2023/03/24 10:22:54 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// # DEFINE OPERATORS "\"\'"

// echo "hi    hello" | grep -n 'el' > outfile


static int	count_tab(char *s, char c, t_prg *prg)
{
	int check;
	int count;
	int i = 0;
	
	count = 0;
	check = 1;
	if (*s)
	{
		if ((*s == '\'') || (*s == '\"'))
		{
			i = has_pair_first(s, prg);
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
				// ft_printf("found \' or \"\n");
				if (has_pair(s, prg) != 0)
				{
					count++;
					s += has_pair(s, prg);
					check = 0;
				}
			}
		}
		s++;
	}
	return (count);	
}

static char *copy_token(const char *s, char c)
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
	char	c;
	int		i;

	c = 32;
	s = prg->input;
	if (!s)
		return (NULL);
	check = 1;
	count = count_tab((char *)s, 32, prg);
	tab = malloc(sizeof(char *) * (count + 1));
	ft_printf("tab: %d\n", count);
	if (!tab)
		return (NULL);
	if (*s)
	{
		if ((*s == '\'') || (*s == '\"'))
		{
			i = has_pair_first(s, prg);
			if (i != 0)
			{
				*tab++ = ft_strndup(s, i);
				// ft_printf("i:%d\n", i);
				s += i;
				check = 0;
				// ft_printf("first: %s\n",s );
			}
		}		
	}
	while (*s)
	{
		if (check && !(*s == c))
		{
			*tab++ = copy_token(s, 32);
			check = 0;
		}
		else if (!check && (*s == c))
		{
			check = 1;
			if ((*(s + 1) == '\'') || (*(s + 1) == '\"'))
			{
				i = has_pair(s, prg);
				if (i != 0)
				{
					*tab++ = ft_strndup(s + 1, i);
					s += i;
					check = 0;
				}
			}
		}
		s++;
		// ft_printf("%s\n",s );
	}
	*tab = 0;
	return (tab - count);
}
