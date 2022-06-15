/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dimi <Dimi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:22:22 by dpaccagn          #+#    #+#             */
/*   Updated: 2021/11/28 00:45:18 by Dimi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*target;
	int		size;
	int		i;

	i = 0;
	size = ft_strlen(src);
	target = malloc(sizeof(char) * size + 1);
	if (!target)
		return (NULL);
	while (src[i])
	{
		target[i] = src[i];
		i++;
	}
	target[i] = '\0';
	return (target);
}

/* **************************************************************************
This function duplicates the src string by allocating the length of the
string to a new place in memory and copying each char into it
°************************************************************************** */
