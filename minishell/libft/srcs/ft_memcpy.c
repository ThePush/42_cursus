/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dimi <Dimi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:42:28 by dpaccagn          #+#    #+#             */
/*   Updated: 2021/11/28 00:37:48 by Dimi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int			i;
	unsigned const char		*c_src;
	unsigned char			*c_dest;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	c_src = (unsigned const char *)src;
	c_dest = (unsigned char *)dest;
	while (i < n)
	{
		c_dest[i] = c_src[i];
		i++;
	}
	return (c_dest);
}

/* **************************************************************************
This function copies a strinf of bytes from src to dest by size n
°************************************************************************** */
