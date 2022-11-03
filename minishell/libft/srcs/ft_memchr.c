/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dimi <Dimi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:06:43 by dpaccagn          #+#    #+#             */
/*   Updated: 2021/11/28 00:33:29 by Dimi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	char			*c_s;
	char			c_n;

	c_s = (char *)s;
	c_n = c;
	i = 0;
	while (i < n)
	{
		if (c_s[i] == c_n)
			return ((void *)c_s + i);
		i++;
	}
	return (NULL);
}

/* **************************************************************************
This function locates the first occurence of c in s, and returns a pointer
to the byte located
°************************************************************************** */
