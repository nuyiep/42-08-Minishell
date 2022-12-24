/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 10:34:18 by plau              #+#    #+#             */
/*   Updated: 2022/11/26 18:59:01 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*output;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		output = malloc(1);
	else if (len >= ft_strlen(s) - start)
		output = malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	else
		output = malloc(sizeof(char) * (len + 1));
	if (output == NULL)
		return (NULL);
	while (i < start)
		i++;
	while (j < len && i < ft_strlen(s))
		output[j++] = s[i++];
	output[j] = '\0';
	return (output);
}
