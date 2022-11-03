/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frames_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 02:03:50 by jsemel            #+#    #+#             */
/*   Updated: 2022/01/04 02:05:25 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

void	count_frames(t_game *game)
{
	if (game->frames < 1)
		game->frames++;
	else
		game->frames = 0;
}

void	animate_player(t_game *game)
{
	if (game->frames == 0 && game->direction == 1)
		game->img_direction = PLAYER_W;
	else if (game->frames == 1 && game->direction == 1)
		game->img_direction = PLAYER_W1;
	else if (game->frames == 0 && game->direction == 2)
		game->img_direction = PLAYER_D;
	else if (game->frames == 1 && game->direction == 2)
		game->img_direction = PLAYER_D1;
	else if (game->frames == 0 && game->direction == 3)
		game->img_direction = PLAYER_S;
	else if (game->frames == 1 && game->direction == 3)
		game->img_direction = PLAYER_S1;
	else if (game->frames == 0 && game->direction == 4)
		game->img_direction = PLAYER_A;
	else if (game->frames == 1 && game->direction == 4)
		game->img_direction = PLAYER_A1;
}
