/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_others.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:35:13 by dpaccagn          #+#    #+#             */
/*   Updated: 2022/06/10 11:21:02 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_xpm(void *mlx, t_texture *texture)
{
	texture->img.img_ptr = mlx_xpm_file_to_image(mlx, texture->path,
			&texture->width, &texture->height);
	texture->img.data = (int *)mlx_get_data_addr(texture->img.img_ptr,
			&texture->img.bpp,
			&texture->img.size_l,
			&texture->img.endian);
}

void	init_rays(t_game *game)
{
	game->rays.arr = malloc(game->datas.res.width * sizeof(t_ray));
	if (!game->rays.arr)
		exit(EXIT_SUCCESS);
	game->rays.fov = deg_to_rad(VIEW_ANGLE);
	game->rays.proj_plane_dist = (game->datas.res.width >> 1)
		/ tan(game->rays.fov / 2);
}

void	init_xpm(t_game *game)
{
	set_xpm(game->mlx.mlx_ptr, &game->datas.no_xpm);
	set_xpm(game->mlx.mlx_ptr, &game->datas.so_xpm);
	set_xpm(game->mlx.mlx_ptr, &game->datas.we_xpm);
	set_xpm(game->mlx.mlx_ptr, &game->datas.ea_xpm);
}
