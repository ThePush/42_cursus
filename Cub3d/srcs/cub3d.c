/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:35:16 by jsemel            #+#    #+#             */
/*   Updated: 2022/06/01 14:35:18 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	int		fd;
	t_game	game;

	check_args(ac, av);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nCould not open file %s.\n", av[1]);
		exit(EXIT_FAILURE);
	}
	load_data(fd, &game.datas);
	if (close(fd) == -1)
	{
		printf("Error\nCould not close file %s.\n", av[1]);
		exit(EXIT_FAILURE);
	}
	check_data(&game.datas);
	display_window(&game);
	return (0);
}
