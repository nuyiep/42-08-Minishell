/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:02:20 by plau              #+#    #+#             */
/*   Updated: 2022/11/26 18:59:01 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_charset(char c, char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
		if (str[i] == c)
			return (1);
	return (0);
}

int	ft_getwc_charset(char const *s, char *str)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (is_charset(s[i], str))
			i++;
		if (s[i] == '\0')
			break ;
		while (s[i] != '\0' && is_charset(s[i], str) == 0)
			i++;
		count++;
	}
	return (count);
}

char	**ft_split_charset(char const *s, char *str)
{
	size_t	i;
	size_t	count;
	char	*wordstart;
	char	**output;

	if (!s)
		return (NULL);
	count = ft_getwc_charset(s, str);
	output = malloc(sizeof(char *) * (count + 1));
	if (output == NULL)
		return (NULL);
	i = 0;
	while (*s != '\0')
	{
		while (is_charset(*s, str))
			s++;
		if (*s == '\0')
			break ;
		wordstart = (char *)s;
		while (*s != '\0' && is_charset(*s, str) == 0)
			s++;
		output[i++] = ft_strndup(wordstart, s - wordstart);
	}
	output[i] = 0;
	return (output);
}
