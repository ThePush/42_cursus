/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:57:00 by jsemel            #+#    #+#             */
/*   Updated: 2021/11/29 10:03:00 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, const char *src, char c)
{
	size_t	i;

	i = 0;
	while (src[i] && src[i] != c)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	ft_size_mem(int i, const char *str, char c)
{
	size_t	len;

	len = 0;
	while (str[i] && str[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

static int	ft_count_words(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (str[i] && str[i] != c)
	{
		count++;
		i++;
	}
	while (str[i] != '\0')
	{
		if (str[i] != c && str[i - 1] == c)
			count++;
		i++;
	}
	return (count);
}

static int	ft_fillin(char const *str, char c, char **result)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			result[j] = malloc(ft_size_mem(i, str, c) + 1);
			if (!result[j])
			{
				while (result[j - 1])
					free(result[j - 1]--);
				free(result);
				return (1);
			}
			ft_strcpy(result[j], &str[i], c);
			i = i + ft_size_mem(i, str, c);
			j++;
		}
		else
			i++;
	}
	return (0);
}

char	**ft_split(char const *str, char c)
{
	int		len;
	char	**result;

	if (!str)
		return (NULL);
	len = ft_count_words(str, c);
	result = malloc((len + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	if (ft_fillin(str, c, result))
		return (NULL);
	result[len] = NULL;
	return (result);
}
