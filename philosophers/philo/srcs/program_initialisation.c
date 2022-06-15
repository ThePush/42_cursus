/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_initialisation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 19:53:25 by jsemel            #+#    #+#             */
/*   Updated: 2022/02/16 22:31:10 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philos(t_data *data)
{
	int	i;

	i = data->nb_philos;
	while (--i >= 0)
	{
		data->philos[i].id = i;
		data->philos[i].ate = 0;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->nb_philos;
		data->philos[i].time_eat = 0;
		data->philos[i].data = data;
	}
}

static int	init_mutex(t_data *data)
{
	int	i;

	i = data->nb_philos;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&data->m_forks[i], NULL) != 0)
			return (ft_perror("could not init m_forks in init_mutex()"), false);
	}
	if (pthread_mutex_init(&data->m_action, NULL) != 0)
		return (ft_perror("could not init m_action in init_mutex()"), false);
	if (pthread_mutex_init(&data->m_eat, NULL) != 0)
		return (ft_perror("could not init m_eat in init_mutex()"), false);
	return (true);
}

static void	init_data(t_data *data, char **av)
{
	data->nb_philos = ft_atol_p(av[1]);
	data->time_to_die = ft_atol_p(av[2]);
	data->time_to_eat = ft_atol_p(av[3]);
	data->time_to_sleep = ft_atol_p(av[4]);
	data->nb_must_eat = -1;
	data->dead = 0;
	data->all_ate = 0;
	if (av[5])
		data->nb_must_eat = ft_atol_p(av[5]);
}

int	init_program(t_data *data, char **av)
{
	init_data(data, av);
	init_philos(data);
	if (!init_mutex(data))
		return (ft_perror("by init_program()"), false);
	return (true);
}
