/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 13:10:27 by plau              #+#    #+#             */
/*   Updated: 2022/11/26 18:59:01 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	int	i;

	i = -1;
	if (!dst || !src)
		return (dst);
	if (dst == src)
		return (dst);
	if (dst > src)
	{
		i = (int)n;
		while (--i >= 0)
			*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
		return (dst);
	}
	while (++i < (int)n)
		*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
	return (dst);
}
