/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaccagn <dpaccagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:11:30 by dpaccagn          #+#    #+#             */
/*   Updated: 2021/11/28 16:50:00 by dpaccagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]) != 0)
	{
		start++;
		if (s1[start] == '\0')
			return (ft_strdup(""));
	}
	while (end > 0 && ft_strchr(set, s1[end - 1]) != 0)
		end--;
	return (ft_substr(s1, start, end - start));
}

/* **************************************************************************
Strtrim returns a copy of the source string trimmed from the set values
It uses strchr to get the end of the string. then substr to make the copy
°************************************************************************** */
