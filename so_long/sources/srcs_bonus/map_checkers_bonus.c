/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checkers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 18:39:06 by jsemel            #+#    #+#             */
/*   Updated: 2022/01/19 12:46:10 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

void	checks_init(t_checks *check)
{
	check->p = 0;
	check->e = 0;
	check->c = 0;
}

// CHECKS IF ONLY AUTHORIZED CHARS ARE IN THE MAP
int	check_chars(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] != '0' && map[y][x] != '1' && map[y][x] != 'C'
					&& map[y][x] != 'E' && map[y][x] != 'P')
				return (CHARERROR);
			x++;
		}
		y++;
	}
	return (0);
}

// CHECKS IF WALLS ARE VALID AND ROWS ARE ALL THE SAME LENGTH
int	check_rowsnwalls(char **map)
{
	int		y;
	size_t	x;
	int		right_wall;
	int		last_row;

	y = 0;
	right_wall = ft_strlen(map[y]) - 1;
	last_row = 0;
	while (map[last_row])
		last_row++;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[0][x] != '1' || map [y][0] != '1'
					|| map[y][right_wall] != '1' || map[last_row - 1][x] != '1')
				return (WALLERROR);
			x++;
		}
		if (x != ft_strlen(map[0]))
			return (ROWERROR);
		y++;
	}
	return (0);
}

// CHECKS IF IS THERE IS ONLY ONE PLAYER, AT LEAST ONE EXIT AND ONE COLLECTIBLE
int	check_counts(char **map, t_checks *check)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
				check->p++;
			if (map[y][x] == 'E')
				check->e++;
			if (map[y][x] == 'C')
				check->c++;
			x++;
		}
		y++;
	}
	if (check->p != 1 || check->e < 1 || check->c == 0)
		return (COUNTERROR);
	return (0);
}

// CHECKS FILE EXTENSION
int	check_file_type(char *file)
{

	if (!file
		|| !ft_strchr(file, '.')
		|| (ft_strcmp(ft_strrchr(file, '.'), ".ber") != 0)
		|| (!file[ft_strrchri(file, '.') - 1])
		|| ((ft_strcmp((&file[ft_strchri(file, '.') - 1]), "/.ber") == 0)))
		return (FILERROR);
	return (0);
}
