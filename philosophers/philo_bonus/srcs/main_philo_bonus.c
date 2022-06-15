/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 19:53:18 by jsemel            #+#    #+#             */
/*   Updated: 2022/02/17 21:53:44 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (!(check_av(ac, av)))
		return (ft_perror("in check_av()"), ft_perror("by main()"), false);
	init_program(&data, av);
	if (!(init_routine(&data)))
		return (ft_perror("by main()"), false);
	return (0);
}
