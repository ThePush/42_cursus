/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_walls_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:35:53 by jsemel            #+#    #+#             */
/*   Updated: 2022/06/10 11:19:04 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	display_wall_ray(t_rect *rect, int *img, t_res *res, t_ray *ray)
{
	int		y;
	int		y_tex;
	int		x_tex;
	double	step;
	double	tex_pox;

	step = rect->tex.height / rect->height;
	tex_pox = (rect->y - res->height / 2 + rect->height / 2) * step;
	x_tex = get_bitmap_offset(ray, rect->tex.width);
	y = -1;
	while (++y < rect->height && y < res->height)
	{
		y_tex = (int)tex_pox & (rect->tex.height - 1);
		tex_pox += step;
		img[(rect->y * res->width) + (y * res->width)
			+ rect->x] = rect->tex.img.data[y_tex * rect->tex.height + x_tex];
	}
}

int	get_bitmap_offset(t_ray *ray, int bitmap_width)
{
	double	remainder;
	int		offset;

	if (ray->side == 'X')
	{
		remainder = ray->x - floor(ray->x);
		offset = bitmap_width * remainder;
	}
	else
	{
		remainder = ray->y - floor(ray->y);
		offset = bitmap_width * remainder;
	}
	return (offset);
}
