/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaccagn <dpaccagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:38:34 by dpaccagn          #+#    #+#             */
/*   Updated: 2021/11/29 12:29:54 by dpaccagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*last;

	if (!new)
		return ;
	if (*alst)
	{
		last = ft_lstlast(*alst);
		last -> next = new;
	}
	else
		*alst = new;
}

/* **************************************************************************
Adds a new t_list at the end of the linked list.
We first create our new element "last", then we check wether our list exists
If it is, our last will be the last element of the linked list,
then we point next from last to a new element.
If there is no list, we create a new element.
°************************************************************************** */
