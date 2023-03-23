/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:00:46 by nchoo             #+#    #+#             */
/*   Updated: 2023/03/23 10:41:14 by nchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// # DEFINE OPERATORS "\"\'"

// echo "hi    hello" | grep -n 'el' > outfile


static int	count_tab(char *s, char c, t_prg *prg)
{
	int check;
	int count;
	
	count = 0;
	check = 1;
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
	// ft_printf("# of tabs: %d\n", count);
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	while (*s)
	{
		if (check && !(*s == c))
		{
			*tab = copy_token(s, 32);
			check = 0;
			tab++;
		}
		else if (!check && (*s == c))
		{
			check = 1;
			if ((*(s + 1) == '\'') | (*(s + 1) == '\"'))
			{
				i = has_pair(s, prg);
				if (i)
				{
					*tab++ = ft_strndup(s + 1, i);
					s += i;
				}
			}
		}
		s++;
	}
	*tab = 0;
	return (tab - count);
}