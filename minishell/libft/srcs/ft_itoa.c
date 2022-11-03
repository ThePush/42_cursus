/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaccagn <dpaccagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:21:45 by dpaccagn          #+#    #+#             */
/*   Updated: 2021/11/29 15:07:55 by dpaccagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nlength(int nb)
{
	size_t	i;

	i = 0;
	if (nb < 0)
	{
		nb = -nb;
		i++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int nb)
{
	unsigned int		i;
	char				*str;

	i = ft_nlength(nb);
	if (nb == 0)
		return (ft_strdup("0"));
	if (nb == -2147483648)
		return (ft_strdup("-2147483648"));
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		str[i] = 48 + (nb % 10);
		nb = nb / 10;
		i--;
	}
	return (str);
}

/* **************************************************************************
This function is like atoi but inversed, it returns an int taken as a para-
meter into a string. The string is filled from the end
Malloc is protected and free of leaks because in the 2 cases where the funct
ion must return something special, there's no malloc yet. You only allocate
when you know you'll fill the string.
°************************************************************************** */
