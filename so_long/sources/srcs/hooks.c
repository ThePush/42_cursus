/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 18:25:13 by jsemel            #+#    #+#             */
/*   Updated: 2021/12/20 11:10:30 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

int	init_resume_window(t_game *game)
{
	xpm_map_load(game, 0, 0);
	return (0);
}

int	key_hooks(int keycode, t_game *game)
{
	if (keycode == ESC)
	{
		exit_game(game);
	}
	if (!game->game_over)
	{
		if (keycode == UP_W || keycode == ARROW_UP)
			move_up(game);
		else if (keycode == LEFT_A || keycode == ARROW_LEFT)
			move_left(game);
		else if (keycode == DOWN_S || keycode == ARROW_DOWN)
			move_down(game);
		else if (keycode == RIGHT_D || keycode == ARROW_RIGHT)
			move_right(game);
	}
	xpm_map_load(game, 0, 0);
	return (0);
}

// MANAGES KEYBOARD AND MOUSE INPUTS
// RED CROSS CLOSE, KEYPRESS, MINIMISE WINDOW
void	inputs(t_game *game)
{
	mlx_hook(game->mlx_win, 33, 1L << 5, &exit_game, game);
	mlx_hook(game->mlx_win, 2, 1L << 0, &key_hooks, game);
	mlx_hook(game->mlx_win, 9, 1L << 21, &init_resume_window, game);
}
