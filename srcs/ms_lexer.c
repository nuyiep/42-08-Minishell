/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:00:46 by nchoo             #+#    #+#             */
/*   Updated: 2023/03/10 18:06:28 by nchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// # DEFINE OPERATORS "\"\'"

// echo "hi    hello" | grep -n 'el' > outfile


static int has_pair(char *s)
{
	char *temp;
	char pair;
	int i;

	i = 1;
	temp = s;
	temp++;
	pair = *temp;
	temp++;

	while (*temp)
	{
		if (*temp == pair)
		{
			ft_printf("i: %d\n", i);
			return (i + 1);
		}
		i++;
		temp++;
	}
	return (0);
}

int	count_tab(char *s, char c)
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
			ft_printf("current count: %d\n", count);
			check = 0;
		}
		else if (!check && (*s == c))
		{
			check = 1;
			if ((*(s + 1) == '\'') | (*(s + 1) == '\"')) 
			{
				ft_printf("found \' or \"\n");
				if (has_pair(s) != 0)
				{
					count++;
					s += has_pair(s);
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
	// ft_printf("copied: %s\n", p);
	return (p);
}

// static char *copy_quoted(const char *s)
// {
	
// }

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
	count = count_tab((char *)s, 32);
	ft_printf("# of tabs: %d\n", count);
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	while (*s)
	{
		if (check && !(*s == c))
		{
			*tab = copy_token(s, 32);
			check = 0;
			// ft_printf("check: %s\n", *tab);
			tab++;
		}
		else if (!check && (*s == c))
		{
			check = 1;
			if ((*(s + 1) == '\'') | (*(s + 1) == '\"'))
			{
				i = has_pair(s);
				if (i)
				{
					*tab++ = ft_strndup(s + 1, i);
					s += i;
				}
			}
		}
		s++;
	}
	/*
	while (*s)
	{
		if (check && !(*s == 32))
		{
			*tab++ = split_strdup(s, 32);
			check = 0;
		}
		else if (!check && (*s == 32))
			check = 1;
		s++;
	}
	*/
	*tab = 0;
	return (tab - count);
}

/*
int main(int ac, char **av)
{
	(void)ac;
	int i = count_tab(av[1], ' ');

	ft_printf("%d\n", i);
}
*/