/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:55:55 by jsemel            #+#    #+#             */
/*   Updated: 2021/11/25 09:09:26 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*little == '\0')
		return ((char *)(big));
	if (*little == '\0')
		return (NULL);
	while (big[i] && (i < len))
	{
		j = 0;
		while ((i + j < len)
			&& (big[i + j] == little[j])
			&& (big[i + j]) && (little[j]))
			j++;
		if (little[j] == '\0')
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
