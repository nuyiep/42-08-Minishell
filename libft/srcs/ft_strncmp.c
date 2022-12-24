/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 16:29:06 by plau              #+#    #+#             */
/*   Updated: 2022/11/26 18:59:01 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;
	int		diff;

	index = -1;
	diff = 0;
	if (n == 0 || (!s1 && !s2))
		return (0);
	if (!s1)
		return (s2[0]);
	if (!s2)
		return (s1[0]);
	while (++index < n && diff == 0 && s1[index] != '\0' && s2[index] != '\0')
		diff = (unsigned char)s1[index] - (unsigned char)s2[index];
	if (index < n && diff == 0 && (s1[index] == '\0' || s2[index] == '\0'))
			diff = (unsigned char)s1[index] - (unsigned char)s2[index];
	return (diff);
}
