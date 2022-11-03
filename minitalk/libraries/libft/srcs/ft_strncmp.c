/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:17:09 by jsemel            #+#    #+#             */
/*   Updated: 2021/11/24 12:51:32 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && (i < n - 1)
		&& ((unsigned char)s1[i] == (unsigned char)s2[i]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
