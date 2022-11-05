/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimioui <dimioui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:08:12 by dpaccagn          #+#    #+#             */
/*   Updated: 2022/04/04 14:44:02 by dimioui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	result = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		{
			if (str[i] == '-')
				sign *= (-1);
		}
		i++;
	}
	while (ft_isnum(str[i]))
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

/* **************************************************************************
This function takes a string as a parameter and returns it as a string
°************************************************************************** */
