/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_program_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 19:53:09 by jsemel            #+#    #+#             */
/*   Updated: 2022/02/17 21:54:24 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	philo_eats(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->nb_philos == 1)
		philo_one(philo);
	else
	{
		sem_wait(data->s_forks);
		philo_does(data, philo->id, "has taken a fork");
		sem_wait(data->s_forks);
		philo_does(data, philo->id, "has taken a fork");
		sem_wait(data->s_eat);
		philo_does(data, philo->id, "is eating");
		philo->time_eat = timestamp();
		sem_post(data->s_eat);
		s_sleep(data->time_to_eat, data);
		(philo->ate)++;
		sem_post(data->s_forks);
		sem_post(data->s_forks);
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

static void	join_and_close(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
		pthread_join(philo[i].philo_thread, NULL);
	sem_close(data->s_forks);
	sem_close(data->s_action);
	sem_close(data->s_eat);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_action");
	sem_unlink("/philo_eat");
}

void	dead_check(t_data *data, t_philo *philo)
{
	int	i;

	while (!(data->all_ate))
	{
		i = -1;
		while (++i < data->nb_philos && !(data->dead))
		{
			sem_wait(data->s_eat);
			if (m_time(philo[i].time_eat, timestamp()) > data->time_to_die)
			{
				philo_does(data, i, "died");
				data->dead = 1;
			}
			sem_post(data->s_eat);
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
	join_and_close(data, philo);
	return (true);
}
