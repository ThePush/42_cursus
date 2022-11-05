/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_x_crossing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaccagn <dpaccagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:34:14 by dpaccagn          #+#    #+#             */
/*   Updated: 2022/06/01 14:34:15 by dpaccagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	x_crossing_south(t_ray *ray, t_map *map, t_player *player)
{
	double	a_x;
	double	a_y;
	double	x_step;
	double	y_step;
	double	ray_section;

	a_y = ceil(player->y);
	y_step = a_y - player->y;
	x_step = y_step / tan(ray->angle);
	a_x = player->x + x_step;
	ray->size += sqrt(pow(x_step, 2) + pow(y_step, 2));
	if (is_wall(map, a_x, a_y, ray))
		return ;
	y_step = 1;
	x_step = y_step / tan(ray->angle);
	ray_section = sqrt(pow(x_step, 2) + pow(y_step, 2));
	while (!is_wall(map, a_x, a_y, ray))
	{
		a_x += x_step;
		a_y += y_step;
		ray->size += ray_section;
	}
}

static void	x_crossing_north(t_ray *ray, t_map *map, t_player *player)
{
	double	a_x;
	double	a_y;
	double	x_step;
	double	y_step;
	double	ray_section;

	a_y = floor(player->y);
	y_step = player->y - a_y;
	x_step = y_step / tan(ray->angle);
	a_x = player->x - x_step;
	ray->size += sqrt(pow(x_step, 2) + pow(y_step, 2));
	if (is_wall(map, a_x, a_y - 1, ray))
		return ;
	y_step = -1;
	x_step = +y_step / tan(ray->angle);
	ray_section = sqrt(pow(x_step, 2) + pow(y_step, 2));
	while (!is_wall(map, a_x, a_y - 1, ray))
	{
		a_x += x_step;
		a_y += y_step;
		ray->size += ray_section;
	}
}

void	matrix_x_crossing(t_ray *ray, t_map *map, t_player *player)
{
	ray->size = 0;
	if (ray->angle == deg_to_rad(180) || ray->angle == deg_to_rad(360))
	{
		ray->size = INT_MAX;
		return ;
	}
	if (south_facing(ray->angle))
		x_crossing_south(ray, map, player);
	else
		x_crossing_north(ray, map, player);
}
