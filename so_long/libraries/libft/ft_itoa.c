/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:33:34 by jsemel            #+#    #+#             */
/*   Updated: 2021/11/29 18:15:47 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nlength(int n)
{
	size_t	i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	size_t		i;
	char		*str;

	if ((long int)n == 0)
		return (ft_strdup("0"));
	if ((long int)n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = ft_nlength((long int)n);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if ((long int)n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while ((long int)n > 0)
	{
		str[i] = 48 + ((long int)n % 10);
		n = n / 10;
		i--;
	}
	return (str);
}
