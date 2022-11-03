/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaccagn <dpaccagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:09:16 by dpaccagn          #+#    #+#             */
/*   Updated: 2021/11/29 14:06:04 by dpaccagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !*f)
		return ;
	while (lst)
	{
		(*f)(lst -> content);
		lst = lst -> next;
	}
}

/* **************************************************************************
This function iters through all of the content of each link of the linked
list and applies the function f to it
°************************************************************************** */
