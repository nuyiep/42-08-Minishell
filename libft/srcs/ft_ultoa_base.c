/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 21:21:24 by plau              #+#    #+#             */
/*   Updated: 2022/11/26 18:59:01 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ultoa_base(unsigned long n)
{
	unsigned long	temp;
	char			*output;
	int				count;

	count = 3;
	temp = n;
	while (temp >= 16 && (temp / 16) && ++count)
		temp /= 16;
	temp = n;
	output = malloc(sizeof(char) * (count + 1));
	if (output == NULL)
		return (NULL);
	output[count] = '\0';
	output[0] = '0';
	output[1] = 'x';
	while (temp >= 16)
	{
		--count;
		output[count] = "0123456789abcdef"[temp % 16];
		temp /= 16;
	}
	output[--count] = "0123456789abcdef"[temp % 16];
	return (output);
}
