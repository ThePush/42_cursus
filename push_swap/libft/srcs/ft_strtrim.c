/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:03:16 by jsemel            #+#    #+#             */
/*   Updated: 2021/11/29 18:24:18 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set && set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*str;

	i = 0;
	start = 0;
	if (!s1)
		return (NULL);
	end = ft_strlen(s1) - 1;
	while (ft_isset(s1[start], set))
		start++;
	if (start == ft_strlen(s1))
		return (ft_strdup(""));
	while (ft_isset(s1[end], set))
		end--;
	str = malloc((end - start + 2) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[start] && start <= end)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
