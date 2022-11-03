/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:24:49 by jsemel            #+#    #+#             */
/*   Updated: 2021/11/25 09:12:00 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*res;

	res = NULL;
	while (lst)
	{
		newlist = ft_lstnew((*f)(lst->content));
		if (!newlist)
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		ft_lstadd_back(&res, newlist);
		newlist = newlist->next;
		lst = lst->next;
	}
	return (res);
}
