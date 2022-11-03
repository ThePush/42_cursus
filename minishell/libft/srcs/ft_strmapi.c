/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaccagn <dpaccagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 10:00:45 by dpaccagn          #+#    #+#             */
/*   Updated: 2021/11/28 16:51:40 by dpaccagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*target;

	if (!s || !f)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	target = malloc (sizeof(char) * (len + 1));
	if (!target)
		return (NULL);
	while (s[i])
	{
		target[i] = f(i, s[i]);
		i++;
	}
	target[i] = '\0';
	return (target);
}

/* **************************************************************************
The function applies a function to each characters of a string
°************************************************************************** */
