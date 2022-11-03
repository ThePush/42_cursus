/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_initialisation_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 19:53:25 by jsemel            #+#    #+#             */
/*   Updated: 2022/03/11 11:14:56 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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

static void	init_semaphores(t_data *data)
{
	sem_unlink("/philo_forks");
	sem_unlink("/philo_action");
	sem_unlink("/philo_eat");
	data->s_forks = sem_open("philo_forks", O_CREAT | O_EXCL,
			S_IRUSR | S_IWUSR, data->nb_philos);
	data->s_action = sem_open("philo_action", O_CREAT | O_EXCL,
			S_IRUSR | S_IWUSR, 1);
	data->s_eat = sem_open("philo_eat", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
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

void	init_program(t_data *data, char **av)
{
	init_data(data, av);
	init_philos(data);
	init_semaphores(data);
}
