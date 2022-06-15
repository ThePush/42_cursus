/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 18:32:44 by jsemel            #+#    #+#             */
/*   Updated: 2022/01/04 01:01:20 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

// CHECKS WANTED DESTINATION AND UPDATES GAMES DATA ACCORDING TO IT
void	update_matrixnplayer(t_game *game, int c)
{
	game->map[game->y][game->x] = '0';
	mlx_destroy_image(game->mlx_ptr, game->p);
	game->moves++;
	count_frames(game);
	animate_player(game);
	game->p = mlx_xpm_file_to_image(game->mlx_ptr, game->img_direction,
			&game->img_width, &game->img_height);
	ft_putstr("\e[1;1H\e[2J");
	print_ascii();
	ft_putstr(KMAG"MOVES = ");
	ft_putnbr_fd(game->moves, 1);
	ft_putchar_fd('\n', 1);
	printf("Pokeball collected %d/%d\n", game->collected,
		game->total_collectibles);
	if (c)
	{
		ft_putstr(KYEL"Pokeball collected !\nRemaining Pokeball(s) : ");
		ft_putnbr_fd((game->total_collectibles) - (game->collected), 1);
		ft_putstr("\n");
	}
	if (game->game_over == 1)
	{
		ft_putstr(KYEL"You win !\nYou can close the window by pressing ESC\n");
		ft_putstr("or clicking the red cross\n"KNRM);
	}
}

void	move_up(t_game *game)
{
	int	x;
	int	y;

	x = game->x;
	y = game->y;
	if (game->map[y - 1][x] == '0')
	{
		game->map[y - 1][x] = 'P';
		game->direction = 1;
		update_matrixnplayer(game, 0);
	}
	else if (game->map[y - 1][x] == 'C')
	{
		game->map[y - 1][x] = 'P';
		game->direction = 1;
		game->collected++;
		update_matrixnplayer(game, 1);
	}
	else if (game->map[y - 1][x] == 'E'
			&& game->collected == game->total_collectibles)
	{
		game->game_over = 1;
		update_matrixnplayer(game, 0);
	}
}

void	move_left(t_game *game)
{
	int	x;
	int	y;

	x = game->x;
	y = game->y;
	if (game->map[y][x - 1] == '0')
	{
		game->map[y][x - 1] = 'P';
		game->direction = 4;
		update_matrixnplayer(game, 0);
	}
	else if (game->map[y][x - 1] == 'C')
	{
		game->map[y][x - 1] = 'P';
		game->direction = 4;
		game->collected++;
		update_matrixnplayer(game, 1);
	}
	else if (game->map[y][x - 1] == 'E'
			&& game->collected == game->total_collectibles)
	{
		game->game_over = 1;
		update_matrixnplayer(game, 0);
	}
}

void	move_down(t_game *game)
{
	int	x;
	int	y;

	x = game->x;
	y = game->y;
	if (game->map[y + 1][x] == '0')
	{
		game->map[y + 1][x] = 'P';
		game->direction = 3;
		update_matrixnplayer(game, 0);
	}
	else if (game->map[y + 1][x] == 'C')
	{
		game->map[y + 1][x] = 'P';
		game->direction = 3;
		game->collected++;
		update_matrixnplayer(game, 1);
	}
	else if (game->map[y + 1][x] == 'E'
			&& game->collected == game->total_collectibles)
	{
		game->game_over = 1;
		update_matrixnplayer(game, 0);
	}
}

void	move_right(t_game *game)
{
	int	x;
	int	y;

	x = game->x;
	y = game->y;
	if (game->map[y][x + 1] == '0')
	{
		game->map[y][x + 1] = 'P';
		game->direction = 2;
		update_matrixnplayer(game, 0);
	}
	else if (game->map[y][x + 1] == 'C')
	{
		game->map[y][x + 1] = 'P';
		game->direction = 2;
		game->collected++;
		update_matrixnplayer(game, 1);
	}
	else if (game->map[y][x + 1] == 'E'
			&& game->collected == game->total_collectibles)
	{
		game->game_over = 1;
		update_matrixnplayer(game, 0);
	}
}
