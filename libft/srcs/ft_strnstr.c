/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:08:42 by plau              #+#    #+#             */
/*   Updated: 2022/11/26 18:59:01 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = -1;
	if (!str || !to_find)
		return (NULL);
	if (to_find[0] == 0)
		return ((char *)str);
	while (str[++i] != '\0' && i < len)
	{
		j = 0;
		while (str[i + j] && to_find[j]
			&& i + j < len && str[i + j] == to_find[j])
			j++;
		if (!to_find[j])
			return ((char *)(str + i));
	}
	return (NULL);
}
