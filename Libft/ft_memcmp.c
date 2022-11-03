/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 20:07:30 by jsemel            #+#    #+#             */
/*   Updated: 2021/11/22 15:39:12 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((i < n - 1)
		&& (*(unsigned char *)(s1 + i) == *(unsigned char *)(s2 + i)))
		i++;
	return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
}
