/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:40:29 by dpaccagn          #+#    #+#             */
/*   Updated: 2022/06/10 11:19:50 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	get_wall_height(t_game *game, t_ray *ray)
{
	double	wall_height;
	double	scaled_distance;
	double	fisheye_adjustment;

	fisheye_adjustment = cos(ray->angle - game->player.rotation_angle);
	scaled_distance = ray->size * SCALE * fisheye_adjustment;
	wall_height = (SCALE / (scaled_distance)) * game->rays.proj_plane_dist;
	return (wall_height);
}

static int	get_top_wall(t_game *game, double wall_height)
{
	double	center_screen;
	double	center_wall;
	int		y;

	center_screen = game->datas.res.height >> 1;
	center_wall = wall_height / 2;
	y = center_screen - center_wall;
	if (y < 0)
		y = 0;
	return (y);
}

static t_texture	get_wall_xpm(t_data *datas, char orientation)
{
	if (orientation == 'N')
		return (datas->no_xpm);
	else if (orientation == 'S')
		return (datas->so_xpm);
	else if (orientation == 'E')
		return (datas->ea_xpm);
	else
		return (datas->we_xpm);
}

void	display_walls(t_game *game)
{
	int		i;
	double	wall_height;
	t_rect	rect;
	t_ray	*ray;

	i = -1;
	while (++i < game->datas.res.width)
	{
		ray = &game->rays.arr[i];
		wall_height = get_wall_height(game, ray);
		rect.x = i;
		rect.y = get_top_wall(game, wall_height);
		rect.height = wall_height;
		rect.tex = get_wall_xpm(&game->datas, ray->orientation);
		display_wall_ray(&rect, game->mlx.img.data, &game->datas.res, ray);
	}
}
