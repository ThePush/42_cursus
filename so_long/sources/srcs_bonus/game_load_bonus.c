/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_load_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 18:43:21 by jsemel            #+#    #+#             */
/*   Updated: 2022/01/04 02:00:34 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

void	count_collectibles(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'C')
				game->total_collectibles++;
			x++;
		}
		y++;
	}
}

// MAP INIT MAKING ALL MAP CHAR MATCH WITH THEIR TILE IMAGES
// INITIALISES PLAYER'S POSITION
// DISPLAYS GAME
void	put_img(t_game *game, void *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win,
		img, x * TILESIZE, y * TILESIZE);
	game->dmove = ft_itoa(game->moves);
	game->pball = ft_itoa(game->collected);
	mlx_string_put(game->mlx_ptr, game->mlx_win, 5, 15, 0xFF0000, "MOVES :");
	mlx_string_put(game->mlx_ptr, game->mlx_win, 5, 29, 0xFF0000, game->dmove);
	mlx_string_put(game->mlx_ptr, game->mlx_win, 4, 13, 0xFFFFFF, "MOVES :");
	mlx_string_put(game->mlx_ptr, game->mlx_win, 4, 27, 0xFFFFFF, game->dmove);
	mlx_string_put(game->mlx_ptr, game->mlx_win, 5, 45, 0xFF0000, "POKEBALLS=");
	mlx_string_put(game->mlx_ptr, game->mlx_win, 5, 59, 0xFF0000, game->pball);
	mlx_string_put(game->mlx_ptr, game->mlx_win, 4, 43, 0xFFFFFF, "POKEBALLS=");
	mlx_string_put(game->mlx_ptr, game->mlx_win, 4, 57, 0xFFFFFF, game->pball);
	free (game->dmove);
	free (game->pball);
}

void	xpm_map_load(t_game *game, int y, int x)
{
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '0')
				put_img(game, game->ground, x, y);
			else if (game->map[y][x] == '1')
				put_img(game, game->wall, x, y);
			else if (game->map[y][x] == 'C')
				put_img(game, game->collectible, x, y);
			else if (game->map[y][x] == 'E')
				put_img(game, game->escape, x, y);
			else if (game->map[y][x] == 'P')
			{
				put_img(game, game->p, x, y);
				game->x = x;
				game->y = y;
			}
			x++;
		}
		y++;
	}
}

void	load_game(t_game *game)
{
	game_init(game);
	count_collectibles(game);
	xpm_init(game);
	xpm_map_load(game, 0, 0);
	ft_putstr(KYEL"Success\nGame loaded\n"KNRM);
}
