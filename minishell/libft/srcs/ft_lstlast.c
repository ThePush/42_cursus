/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaccagn <dpaccagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:26:26 by dpaccagn          #+#    #+#             */
/*   Updated: 2021/11/29 11:45:33 by dpaccagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}

/* **************************************************************************
This function goes to the last element of a linked list and returns it
We first ask if lst exists, if not we return a NULL pointer
Then we loop while we can through next in the list and go to the last element
°************************************************************************** */
