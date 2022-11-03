/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaccagn <dpaccagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:46:15 by dpaccagn          #+#    #+#             */
/*   Updated: 2021/11/29 12:34:31 by dpaccagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (del)
		del(lst -> content);
	free (lst);
}

/* **************************************************************************
This function deletes one element from the linked list. First we check if
the list exists. If not we exit, then if del exists we delete the content of
the pointed element, and free memory
°************************************************************************** */
