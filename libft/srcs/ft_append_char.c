/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:03:07 by schuah            #+#    #+#             */
/*   Updated: 2022/12/11 13:48:57 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_append_char(char *input, char c)
{
	char	*output;
	int		size;
	int		i;

	i = -1;
	size = 0;
	if (input != NULL)
		size = ft_strlen(input);
	output = ft_calloc(size + 2, sizeof(char));
	if (input != NULL)
	{
		while (input[++i] != '\0')
			output[i] = input[i];
	}
	output[i] = c;
	output[i + 1] = '\0';
	free(input);
	return (output);
}
