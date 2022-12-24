/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_to_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 20:34:51 by schuah            #+#    #+#             */
/*   Updated: 2022/12/11 13:51:36 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_list_to_array(t_list *lst, int elem_size)
{
	void	*buffer;
	void	*head;

	if (lst == NULL)
		return (NULL);
	buffer = ft_calloc(ft_lstsize(lst), elem_size);
	head = buffer;
	while (lst != NULL)
	{
		ft_memcpy(buffer, lst->content, elem_size);
		lst = lst->next;
		buffer += elem_size;
	}
	return (head);
}
