/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 19:53:52 by jsemel            #+#    #+#             */
/*   Updated: 2022/02/16 22:22:58 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + t.tv_usec / 1000);
}

long long	m_time(long long past, long long pres)
{
	return (pres - past);
}

void	s_sleep(long long time, t_data *data)
{
	long long	i;

	i = timestamp();
	while (!(data->dead))
	{
		if (m_time(i, timestamp()) >= time)
			break ;
		usleep(50);
	}
}

void	philo_does(t_data *data, int id, char *str)
{
	pthread_mutex_lock(&data->m_action);
	if (!(data->dead))
	{
		printf("%lli\t|", timestamp() - data->start_time);
		printf(" philo [%i] ", id + 1);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&data->m_action);
	return ;
}

void	philo_one(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	philo_does(data, philo->id, "has taken a fork");
	s_sleep(data->time_to_die, data);
	dead_check(data, data->philos);
}
