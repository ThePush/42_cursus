/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:32:54 by dpaccagn          #+#    #+#             */
/*   Updated: 2022/06/10 11:22:11 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	player_movement(t_player *player, char **grid)
{
	double	move_step;
	double	rotation;
	double	tmp_x;
	double	tmp_y;

	if (player->move_direction == 0)
		return ;
	move_step = player->move_speed;
	rotation = player->rotation_angle;
	if (player->move_direction == 's')
		move_step = (-1) * player->move_speed;
	else if (player->move_direction == 'a')
	{
		move_step = (-1) * player->move_speed;
		rotation = player->rotation_angle + deg_to_rad(90);
	}
	else if (player->move_direction == 'd')
		rotation = player->rotation_angle + deg_to_rad(90);
	tmp_x = player->x + (cos(rotation) * move_step);
	if (grid[(int)floor(player->y)][(int)floor(tmp_x)] == '0')
		player->x = tmp_x;
	tmp_y = player->y + (sin(rotation) * move_step);
	if (grid[(int)floor(tmp_y)][(int)floor(player->x)] == '0')
		player->y = tmp_y;
}

static void	player_angle(t_player *player)
{
	double	rotation;

	if (player->turn_direction == 0)
		return ;
	rotation = player->turn_direction * player->rotation_speed;
	player->rotation_angle += rotation;
}

static void	raycasting(t_game *game)
{
	double	ray_angle;
	int		i;

	ray_angle = game->player.rotation_angle - game->rays.fov / 2;
	i = -1;
	while (++i < game->datas.res.width)
	{
		game->rays.arr[i].angle = ray_angle;
		get_rays(&game->rays.arr[i], &game->datas.map, &game->player);
		ray_angle += game->rays.fov / game->datas.res.width;
	}
}

void	update(t_game *game)
{
	player_movement(&game->player, game->datas.map.matrix);
	player_angle(&game->player);
	raycasting(game);
}
