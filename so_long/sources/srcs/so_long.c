/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 18:28:04 by jsemel            #+#    #+#             */
/*   Updated: 2022/01/04 01:58:46 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

int	valid_map(char **map, char *file)
{
	t_checks	check;

	checks_init(&check);
	if (check_file_type(file) == FILERROR)
		return (ft_putstr(KRED"Error\nInvalid file type, should be *.ber\n"KNRM));
	else if (check_chars(map) == CHARERROR)
		return (ft_putstr(KRED"Error\nInvalid set of characters in file\n"KNRM));
	else if (check_rowsnwalls(map) == WALLERROR)
		return (ft_putstr(KRED"Error\nInvalid wall setting in the map\n"KNRM));
	else if (check_rowsnwalls(map) == ROWERROR)
		return (ft_putstr(KRED"Error\nInvalid row configuration in file\n"KNRM));
	else if (check_counts(map, &check) == COUNTERROR)
		return (ft_putstr(KRED"Error\nInvalid map\n"KNRM));
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac == 2)
	{
		game.map = create_matrix(av[1]);
		if (!game.map)
			return (ft_putstr(KRED"Error\nInvalid map\n"KNRM));
		if (!valid_map(game.map, av[1]))
		{
			print_ascii();
			load_game(&game);
			inputs(&game);
			mlx_loop(game.mlx_ptr);
		}
		else
			free_matrix(&game);
	}
	else
		ft_putstr(KRED"Error\nPlease put a <map>.ber as argument\n"KNRM);
	return (0);
}
