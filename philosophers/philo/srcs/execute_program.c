/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_program.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 19:53:09 by jsemel            #+#    #+#             */
/*   Updated: 2022/02/16 22:07:36 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_eats(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->nb_philos == 1)
		philo_one(philo);
	else
	{
		pthread_mutex_lock(&data->m_forks[philo->left_fork]);
		philo_does(data, philo->id, "has taken a fork");
		pthread_mutex_lock(&data->m_forks[philo->right_fork]);
		philo_does(data, philo->id, "has taken a fork");
		pthread_mutex_lock(&data->m_eat);
		philo_does(data, philo->id, "is eating");
		philo->time_eat = timestamp();
		pthread_mutex_unlock(&data->m_eat);
		s_sleep(data->time_to_eat, data);
		(philo->ate)++;
		pthread_mutex_unlock(&data->m_forks[philo->left_fork]);
		pthread_mutex_unlock(&data->m_forks[philo->right_fork]);
	}
}

static void	*routine(void *void_philo)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)void_philo;
	data = philo->data;
	if (philo->id % 2)
		usleep(20000);
	while (!(data->dead))
	{
		philo_eats(philo);
		if (data->all_ate)
			break ;
		philo_does(data, philo->id, "is sleeping");
		s_sleep(data->time_to_sleep, data);
		philo_does(data, philo->id, "is thinking");
	}
	return (NULL);
}

static void	join_and_destroy(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
		pthread_join(philo[i].philo_thread, NULL);
	i = -1;
	while (++i < data->nb_philos)
		pthread_mutex_destroy(&data->m_forks[i]);
	pthread_mutex_destroy(&data->m_action);
}

void	dead_check(t_data *data, t_philo *philo)
{
	int	i;

	while (!(data->all_ate))
	{
		i = -1;
		while (++i < data->nb_philos && !(data->dead))
		{
			pthread_mutex_lock(&data->m_eat);
			if (m_time(philo[i].time_eat, timestamp()) > data->time_to_die)
			{
				philo_does(data, i, "died");
				data->dead = 1;
			}
			pthread_mutex_unlock(&data->m_eat);
			usleep(1000);
		}
		if (data->dead)
			break ;
		i = 0;
		while ((data->nb_must_eat != -1) && (i < data->nb_philos)
			&& (philo[i].ate >= data->nb_must_eat))
			i++;
		if (i == data->nb_philos)
			data->all_ate = 1;
	}
}

int	init_routine(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = data->philos;
	data->start_time = timestamp();
	while (i < data->nb_philos)
	{
		if (pthread_create(&philo[i].philo_thread, NULL, &routine, &philo[i]))
			return (ft_perror("pthread_create in init_routine()"), false);
		philo[i].time_eat = timestamp();
		i++;
	}
	dead_check(data, data->philos);
	join_and_destroy(data, philo);
	return (true);
}
