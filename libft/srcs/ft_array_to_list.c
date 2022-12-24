/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_to_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 20:33:35 by schuah            #+#    #+#             */
/*   Updated: 2022/12/11 13:49:10 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* To use: ft_printf("%type\n", *(type *)content); */
t_list	*ft_array_to_list(void *array, int array_size, int elem_size)
{
	t_list	*head;
	void	*content;
	int		i;

	head = NULL;
	i = -1;
	while (++i < array_size)
	{
		content = ft_calloc(1, elem_size);
		ft_memcpy(content, array, elem_size);
		ft_lstadd_back(&head, ft_lstnew(content));
		array += elem_size;
	}
	return (head);
}
