/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimioui <dimioui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 10:52:49 by dpaccagn          #+#    #+#             */
/*   Updated: 2022/04/05 16:17:47 by dimioui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//char	*ft_strjoin(char const *s1, char const *s2)
//{
//	size_t	i;
//	size_t	j;
//	size_t	len;
//	char	*target;

//	if (!s1 || !s2)
//		return (NULL);
//	len = ft_strlen(s1) + ft_strlen(s2) + 1;
//	target = malloc (sizeof (char) * len);
//	if (!target)
//		return (NULL);
//	i = 0;
//	while (s1[i])
//	{
//		target[i] = s1[i];
//		i++;
//	}
//	j = 0;
//	while (s2[j])
//	{
//		target[i + j] = s2[j];
//		j++;
//	}
//	target[i + j] = '\0';
//	return (target);
//}

/* **************************************************************************
Strjoin is a function that concatenate 2 strings into one string.
°************************************************************************** */

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len_s1;
	int		len_s2;
	char	*s3;
	int		i;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	i = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	s3 = (char *)malloc(len_s1 + len_s2 + 1);
	if (s3 == NULL)
		return (NULL);
	while (i < len_s1 || i < len_s2)
	{
		if (i < len_s1)
			s3[i] = s1[i];
		if (i < len_s2)
			s3[i + len_s1] = s2[i];
		i++;
	}
	s3[len_s1 + len_s2] = '\0';
	return (s3);
}
