/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 18:55:09 by schuah            #+#    #+#             */
/*   Updated: 2022/12/11 13:52:36 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*head;

	if (!lst || !f || !del)
		return (NULL);
	newlist = ft_lstnew((*f)(lst->content));
	if (newlist == NULL)
		return (NULL);
	(void)(*del);
	lst = lst->next;
	head = newlist;
	while (lst != NULL)
	{
		newlist->next = ft_lstnew((*f)(lst->content));
		newlist = newlist->next;
		if (newlist == NULL)
			return (NULL);
		lst = lst->next;
	}
	return (head);
}
