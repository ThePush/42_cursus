/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaccagn <dpaccagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:39:39 by dpaccagn          #+#    #+#             */
/*   Updated: 2022/06/01 14:39:44 by dpaccagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_rays(t_ray *ray, t_map *map, t_player *player)
{
	t_ray	x_crossing;
	t_ray	y_crossing;

	x_crossing.angle = modulo_radian(ray->angle);
	y_crossing.angle = modulo_radian(ray->angle);
	x_crossing.side = 'X';
	y_crossing.side = 'Y';
	matrix_x_crossing(&x_crossing, map, player);
	matrix_y_crossing(&y_crossing, map, player);
	if (x_crossing.size <= y_crossing.size)
		*ray = x_crossing;
	else
		*ray = y_crossing;
}
