/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:47:20 by jsemel            #+#    #+#             */
/*   Updated: 2021/11/25 09:12:58 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned long	i;

	if (!dest && !src)
		return (NULL);
	if (dest > src)
	{
		while (n--)
			*(unsigned char *)(dest + n) = *(unsigned char *)(src + n);
	}
	else
	{
		i = 0;
		while (n--)
		{
			*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
			i++;
		}
	}
	return (dest);
}
