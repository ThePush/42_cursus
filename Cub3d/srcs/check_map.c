/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:08:31 by dpaccagn          #+#    #+#             */
/*   Updated: 2022/06/01 15:25:54 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	valid_chars_in_map(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!ft_strchr("01NSEW ", map[i][j]))
				return (false);
		}
	}
	return (true);
}

static bool	check_walls(char **map, t_map m)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] != '1' && map[i][j] != ' ')
			{
				if (i == 0 || j == 0 || i == m.height - 1 || j == m.width - 1)
					return (false);
				else if (map[i - 1][j - 1] == ' ' || map[i - 1][j] == ' '
						|| map[i - 1][j + 1] == ' ' || map[i][j + 1] == ' '
						|| map[i + 1][j + 1] == ' ' || map[i + 1][j] == ' '
						|| map[i + 1][j - 1] == ' ' || map[i][j - 1] == ' ')
					return (false);
			}
		}
	}
	return (true);
}

static bool	check_player(char **map)
{
	int	nb_player;
	int	i;
	int	j;

	nb_player = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (ft_strchr("NSEW", map[i][j]))
				nb_player++;
			if (nb_player > 1)
				return (false);
		}
	}
	if (nb_player == 1)
		return (true);
	return (false);
}

void	check_map(t_data *datas)
{
	if (datas->map.matrix == 0)
	{
		ft_perror("check_map(): no map found");
		ft_usage("Please provide a map in the .cub file");
		free_datas(datas);
		exit(EXIT_FAILURE);
	}
	else if (!valid_chars_in_map(datas->map.matrix))
	{
		ft_perror("check_map(): Wrong character found in map");
		ft_usage(KGRN"Authorized characters: 01NSEW");
		free_datas(datas);
		exit(EXIT_FAILURE);
	}
}

void	check_map2(t_data *datas)
{
	if (!check_walls(datas->map.matrix, datas->map))
	{
		ft_perror("check_map(): Wall missing");
		ft_usage("The map must be surrounded by '1' and should not have holes");
		free_datas(datas);
		exit(EXIT_FAILURE);
	}
	else if (!check_player(datas->map.matrix))
	{
		ft_perror("check_map(): Wrong number of players in map");
		ft_usage("There must be ONE player in the map, defined by N/S/E/W");
		free_datas(datas);
		exit(EXIT_FAILURE);
	}
}
