/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaccagn <dpaccagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:45:21 by dpaccagn          #+#    #+#             */
/*   Updated: 2022/06/01 14:45:22 by dpaccagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	get_starting_orientation(char orientation)
{
	double	radian;

	radian = 0;
	if (orientation == 'N')
		radian = deg_to_rad(270);
	else if (orientation == 'S')
		radian = deg_to_rad(90);
	else if (orientation == 'E')
		radian = deg_to_rad(360);
	else if (orientation == 'W')
		radian = deg_to_rad(180);
	return (radian);
}

static void	get_starting_position(t_player *player, char **matrix)
{
	int	i;
	int	j;

	i = -1;
	while (matrix[++i])
	{
		j = -1;
		while (matrix[i][++j])
		{
			if (ft_strchr("NSEW", matrix[i][j]))
			{
				player->x = j + 0.5;
				player->y = i + 0.5;
				player->rotation_angle = get_starting_orientation(matrix[i][j]);
				matrix[i][j] = '0';
			}
		}
	}
}

void	init_player(t_game *game)
{
	game->player.move_direction = 0;
	game->player.move_speed = 0.15;
	game->player.turn_direction = 0;
	game->player.rotation_speed = deg_to_rad(4);
	get_starting_position(&game->player, game->datas.map.matrix);
}
