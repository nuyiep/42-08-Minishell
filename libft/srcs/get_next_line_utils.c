/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 20:34:26 by schuah            #+#    #+#             */
/*   Updated: 2022/07/18 11:13:31 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

char	*ft_strcomb(char *dst, char *src)
{
	int		i;
	int		j;
	char	*output;

	if (dst == NULL)
	{
		dst = malloc(sizeof(char) * 1);
		if (dst == NULL || src == NULL)
			return (NULL);
		dst[0] = '\0';
	}
	output = malloc(sizeof(char)
			* ((int)ft_strlen(dst) + (int)ft_strlen(src) + 1));
	if (output == NULL)
		return (NULL);
	i = -1;
	if (dst)
		while (dst[++i] != '\0')
			output[i] = dst[i];
	j = 0;
	while (src[j] != '\0')
		output[i++] = src[j++];
	output[(int)ft_strlen(dst) + (int)ft_strlen(src)] = '\0';
	free(dst);
	return (output);
}

int	checkend(char c)
{
	return (c != '\0' && c != '\n');
}
