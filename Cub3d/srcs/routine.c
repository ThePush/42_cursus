/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:43:15 by dpaccagn          #+#    #+#             */
/*   Updated: 2022/06/10 11:26:20 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	display_window(t_game *game)
{
	game->mlx.mlx_ptr = mlx_init();
		game->mlx.win = mlx_new_window(game->mlx.mlx_ptr,
			game->datas.res.width,
			game->datas.res.height,
			"Cub3d");
	init_all(game);
	mlx_loop_hook(game->mlx.mlx_ptr, routine, game);
	mlx_loop(game->mlx.mlx_ptr);
}

int	routine(void *my_struct)
{
	t_game	*game;

	game = my_struct;
	game->mlx.img.img_ptr = mlx_new_image(game->mlx.mlx_ptr,
			game->datas.res.width,
			game->datas.res.height);
	game->mlx.img.data = (int *)mlx_get_data_addr(game->mlx.img.img_ptr,
			&game->mlx.img.bpp,
			&game->mlx.img.size_l,
			&game->mlx.img.endian);
	update(game);
	display_game(game);
	mlx_put_image_to_window(game->mlx.mlx_ptr,
		game->mlx.win,
		game->mlx.img.img_ptr,
		0,
		0);
	mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.img.img_ptr);
	return (true);
}
