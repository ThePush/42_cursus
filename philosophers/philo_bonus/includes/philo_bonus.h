/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 19:52:45 by jsemel            #+#    #+#             */
/*   Updated: 2022/03/11 11:14:05 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

// Libraries
# include <sys/time.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdint.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

// ANSI color codes
# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"

// Constants
# define MAX_PHILO 200
# define ERROR -1

// Structures
typedef struct s_philo
{
	int					id;
	int					ate;
	int					left_fork;
	int					right_fork;
	long long			time_eat;
	pthread_t			philo_thread;
	struct s_data		*data;
}	t_philo;

typedef struct s_data
{
	int					nb_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_must_eat;
	int					dead;
	int					all_ate;
	long long			start_time;
	sem_t				*s_forks;
	sem_t				*s_eat;
	sem_t				*s_action;
	t_philo				philos[MAX_PHILO];
}	t_data;

// utils
void			ft_perror(const char *str);
int				ft_strlen(char *str);

// program_initialisation
void			init_program(t_data *data, char **av);

// check_av
int				check_av(int ac, char **av);
long			ft_atol_p(const char *str);

// execute_program
void			dead_check(t_data *data, t_philo *philo);
int				init_routine(t_data *data);

// utils_philo
void			philo_does(t_data *data, int id, char *str);
void			s_sleep(long long time, t_data *data);
void			philo_one(t_philo *philo);
long long		m_time(long long past, long long pres);
long long		timestamp(void);

#endif
