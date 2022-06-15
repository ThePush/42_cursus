/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaccagn <dpaccagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:15:03 by dpaccagn          #+#    #+#             */
/*   Updated: 2021/11/29 14:05:29 by dpaccagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*ptr;

	if (!del || !*lst)
		return ;
	ptr = *lst;
	while (ptr)
	{
		tmp = ptr -> next;
		ft_lstdelone(ptr, del);
		ptr = tmp;
	}
	*lst = (NULL);
}

/* **************************************************************************
This function goes through all the links of your linked list and deletes all
of its content then frees all the memory allocated. (with lstdelone).
It then creates a pointer to NULL at the beginning of the list
°************************************************************************** */
