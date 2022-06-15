/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaccagn <dpaccagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:24:48 by dpaccagn          #+#    #+#             */
/*   Updated: 2021/11/29 13:15:07 by dpaccagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)(big));
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while ((big[i + j] == little[j]) && (i + j < len)
			&& (big[i + j] && little[j]))
			j++;
		if (little[j] == '\0')
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}

/* **************************************************************************
This function locates the first occurence of little string in big string
if little is empty, big is returned
if little occurs nowhere, NULL is returned
UNFINISHED
°************************************************************************** */
