/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 11:05:14 by jsemel            #+#    #+#             */
/*   Updated: 2022/01/18 11:05:16 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

void	window_size(t_game *game)
{
	size_t	i;

	i = 0;
	game->window_width = ft_strlen(game->map[i]) * TILESIZE;
	game->window_height = 0;
	while (game->map[i])
		i++;
	game->window_height = i * TILESIZE;
}

void	game_init(t_game *game)
{
	window_size(game);
	game->moves = 0;
	game->total_collectibles = 0;
	game->collected = 0;
	game->game_over = 0;
	game->dmove = "0";
	game->frames = 0;
	game->direction = 0;
	game->mlx_ptr = mlx_init();
	game->mlx_win = mlx_new_window
		(game->mlx_ptr, game->window_width, game->window_height, "so_long");
}

void	xpm_init(t_game *game)
{
	game->ground = mlx_xpm_file_to_image(game->mlx_ptr, GROUND_0,
			&game->img_width, &game->img_height);
	game->wall = mlx_xpm_file_to_image(game->mlx_ptr, WALL_1,
			&game->img_width, &game->img_height);
	game->collectible = mlx_xpm_file_to_image(game->mlx_ptr, COLLECTIBLE_C,
			&game->img_width, &game->img_height);
	game->escape = mlx_xpm_file_to_image(game->mlx_ptr, EXIT_E,
			&game->img_width, &game->img_height);
	game->p = mlx_xpm_file_to_image(game->mlx_ptr, PLAYER_P,
			&game->img_width, &game->img_height);
}
