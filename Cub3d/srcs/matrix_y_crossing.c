/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_y_crossing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaccagn <dpaccagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:42:52 by dpaccagn          #+#    #+#             */
/*   Updated: 2022/06/01 14:42:53 by dpaccagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	y_crossing_west(t_ray *ray, t_map *map, t_player *player)
{
	double	a_x;
	double	a_y;
	double	x_step;
	double	y_step;
	double	ray_section;

	a_x = floor(player->x);
	x_step = player->x - a_x;
	y_step = x_step * tan(ray->angle);
	a_y = player->y - y_step;
	ray->size += sqrt(pow(x_step, 2) + pow(y_step, 2));
	if (is_wall(map, a_x - 1, a_y, ray))
		return ;
	x_step = -1;
	y_step = x_step * tan(ray->angle);
	ray_section = sqrt(pow(x_step, 2) + pow(y_step, 2));
	while (!is_wall(map, a_x - 1, a_y, ray))
	{
		a_x += x_step;
		a_y += y_step;
		ray->size += ray_section;
	}
}

static void	y_crossing_east(t_ray *ray, t_map *map, t_player *player)
{
	double	a_x;
	double	a_y;
	double	x_step;
	double	y_step;
	double	ray_section;

	a_x = ceil(player->x);
	x_step = a_x - player->x;
	y_step = x_step * tan(ray->angle);
	a_y = player->y + y_step;
	ray->size += sqrt(pow(x_step, 2) + pow(y_step, 2));
	if (is_wall(map, a_x, a_y, ray))
		return ;
	x_step = 1;
	y_step = x_step * tan(ray->angle);
	ray_section = sqrt(pow(x_step, 2) + pow(y_step, 2));
	while (!is_wall(map, a_x, a_y, ray))
	{
		a_x += x_step;
		a_y += y_step;
		ray->size += ray_section;
	}
}

void	matrix_y_crossing(t_ray *ray, t_map *map, t_player *player)
{
	ray->size = 0;
	if (ray->angle == deg_to_rad(90) || ray->angle == deg_to_rad(270))
	{
		ray->size = INT_MAX;
		return ;
	}
	if (west_facing(ray->angle))
		y_crossing_west(ray, map, player);
	else
		y_crossing_east(ray, map, player);
}
