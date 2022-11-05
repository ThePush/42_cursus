/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:40:50 by dpaccagn          #+#    #+#             */
/*   Updated: 2022/06/10 11:17:48 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	display_rect(t_rect *rect, int *img, int res_width)
{
	int	i;
	int	j;
	int	tmp_x;
	int	tmp_y;

	rect->border_width--;
	i = -1;
	while (++i < rect->height)
	{
		j = -1;
		while (++j < rect->width)
		{
			tmp_x = rect->x + j;
			tmp_y = rect->y + i;
			if (i <= rect->border_width || j <= rect->border_width
				|| i >= rect->height - 1 - rect->border_width
				|| j >= rect->width - 1 - rect->border_width)
				img[tmp_y * res_width + tmp_x] = rect->border_color;
			else
				img[tmp_y * res_width + tmp_x] = rect->fill_color;
		}
	}
}

static void	display_ceilling(t_game *game)
{
	t_rect	rect;

	rect.x = 0;
	rect.y = 0;
	rect.width = game->datas.res.width;
	rect.height = game->datas.res.height >> 1;
	rect.border_width = 0;
	rect.fill_color = game->datas.ceilling.argb;
	rect.border_color = 0;
	display_rect(&rect, game->mlx.img.data, game->datas.res.width);
}

static void	display_floor(t_game *game)
{
	t_rect	rect;

	rect.x = 0;
	rect.y = game->datas.res.height >> 1;
	rect.width = game->datas.res.width;
	rect.height = game->datas.res.height >> 1;
	rect.border_width = 0;
	rect.fill_color = game->datas.floor.argb;
	rect.border_color = 0;
	display_rect(&rect, game->mlx.img.data, game->datas.res.width);
}

void	display_game(t_game *game)
{
	display_ceilling(game);
	display_floor(game);
	display_walls(game);
}
