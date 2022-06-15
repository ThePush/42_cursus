/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_av.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:50:20 by jsemel            #+#    #+#             */
/*   Updated: 2022/03/10 11:52:28 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol_p(const char *str)
{
	size_t	i;
	long	nb;

	i = 0;
	nb = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (ERROR);
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i] - 48;
		i++;
	}
	if (str[i] || nb > 2147483648 || nb < 0)
		return (ERROR);
	return (nb);
}

int	check_av(int ac, char **av)
{
	size_t	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (ft_perror("wrong argument number"), false);
	while (av[i])
	{
		if (ft_atol_p(av[i]) == ERROR || ft_strlen(av[i]) > 10)
			return (ft_perror("wrong argument format"), false);
		i++;
	}
	if (ft_atol_p(av[1]) < 1)
		return (ft_perror("there must be at least one philosopher"), false);
	if (ft_atol_p(av[1]) > 200)
		return (ft_perror("there must be at most 200 philosophers"), false);
	if (av[5] && (ft_atol_p(av[5]) < 1))
		return (ft_perror("number of meals must be superior to zero"), false);
	return (true);
}
