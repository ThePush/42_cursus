/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaccagn <dpaccagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 09:54:07 by dpaccagn          #+#    #+#             */
/*   Updated: 2021/11/28 16:49:46 by dpaccagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*target;
	unsigned int	i;
	unsigned int	j;

	if (!s)
		return (NULL);
	j = ft_strlen(s);
	if (start >= j)
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	target = malloc(sizeof(char) * len + 1);
	if (!target)
		return (NULL);
	while (start--)
		s++;
	i = 0;
	while (i < len)
	{
		target[i] = s[i];
		i++;
	}
	target[i] = '\0';
	return (target);
}

/* **************************************************************************
Like strdup but this function gives you the choice of the size len to copy
into a new string
°************************************************************************** */
