/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchoo <nchoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:00:46 by nchoo             #+#    #+#             */
/*   Updated: 2023/02/25 17:28:00 by nchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// # DEFINE OPERATORS "\"\'"

// echo "hi    hello" | grep -n 'el' > outfile


static void has_pair(char **s)
{
	char *temp;
	char pair;

	temp = *s;
	pair = *temp;
	temp++;
	ft_printf("start: %s\n", temp);
	while (*temp)
	{
		if (*temp == pair)
		{
			*s = temp;
			break;
		}
		temp++;
	}
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
			check = 0;
		}
		else if (!check && (*s == c))
		{
			check = 1;
			ft_printf("%s\n", s+1);
			if ((*(s + 1) == '\'' | *(s + 1) == '\"'))
				has_pair(&s);
		}
		s++;
	}
	return (count);	
}


/*
static char *split_strdup(const char *s, char c)
{
	char *tmp;
	char *p;
	int i;

	i = 0;
	while (s[i] && !(s[i] == c))
	i++;
	p = malloc(sizeof(char) * (i + 1));
	tmp = p;
	while (i-- > 0)
		*tmp++ = *(char *)s++;
	*tmp = '\0';
	return (p);
}
*/

// char **split_token(t_prg prg, char *s)
// {
// 	char	**tab;
// 	int		count;
// 	int		check;

// 	if (!s)
// 		return (NULL);
// 	check = 1;
// 	count = count_tab((char *)s, c);
// 	tab = malloc(sizeof(char *) * (count + 1));
// 	if (!tab)
// 		return (NULL);
// 	while (*s)
// 	{
// 		if (check && !(*s == c))
// 		{
// 			*tab++ = split_strdup(s, c);
// 			check = 0;
// 		}
// 		else if (!check && (*s == c))
// 			check = 1;
// 		s++;
// 	}
// 	*tab = 0;
// 	return (tab - count);
// }

int main(int ac, char **av)
{
	(void)ac;
	int i = count_tab(av[1], ' ');

	ft_printf("%d", i);
}