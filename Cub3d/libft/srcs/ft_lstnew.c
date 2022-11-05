/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dimi <Dimi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:53:23 by dpaccagn          #+#    #+#             */
/*   Updated: 2021/11/28 00:31:34 by Dimi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof (t_list));
	if (new != NULL)
	{
		new -> content = content;
		new -> next = NULL;
	}
	return (new);
}
/* **************************************************************************
This function creates a new structure pointed to by the one created previous
ly and fills it with the content parameter
°************************************************************************** */
