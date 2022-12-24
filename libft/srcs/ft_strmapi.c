/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 15:43:55 by plau              #+#    #+#             */
/*   Updated: 2022/11/26 18:59:01 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*output;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
		i++;
	output = malloc(sizeof(char) * (i + 1));
	if (output == NULL)
		return (NULL);
	i = -1;
	while (s[++i] != '\0')
		output[i] = (*f)(i, s[i]);
	output[i] = '\0';
	return (output);
}
