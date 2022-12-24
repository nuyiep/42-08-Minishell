/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 21:19:17 by plau              #+#    #+#             */
/*   Updated: 2022/11/26 18:59:01 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_uitoa_base(unsigned int n, char *base)
{
	int				i;
	char			*output;
	unsigned int	temp;

	i = 1;
	temp = n;
	while (temp >= 16 && (temp / 16) > 0 && ++i)
		temp /= 16;
	output = malloc(sizeof(char) * (i + 1));
	output[i] = '\0';
	while (n >= 16)
	{
		output[--i] = base[n % 16];
		n /= 16;
	}
	output[--i] = base[n % 16];
	return (output);
}
