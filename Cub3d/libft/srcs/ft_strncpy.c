/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:52:58 by dimioui           #+#    #+#             */
/*   Updated: 2022/06/01 16:01:02 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strnlen(const char *str, size_t n)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i] && i < n)
		i++;
	return (i);
}

char	*ft_strncpy(char *dest, char *src, size_t size)
{
	size_t	n;

	n = ft_strnlen(src, size);
	if (n != size)
		ft_memset(dest + size, '\0', size - n);
	return (ft_memcpy(dest, src, size));
}
