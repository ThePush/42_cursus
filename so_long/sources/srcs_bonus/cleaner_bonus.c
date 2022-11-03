/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 18:30:03 by jsemel            #+#    #+#             */
/*   Updated: 2022/01/18 11:47:32 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

void	free_matrix(t_game *game)
{
	int	i;

	i = 0;
	if (!game)
		return ;
	while (game->map[i])
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
}

void	free_game(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->ground);
	mlx_destroy_image(game->mlx_ptr, game->wall);
	mlx_destroy_image(game->mlx_ptr, game->collectible);
	mlx_destroy_image(game->mlx_ptr, game->escape);
	mlx_destroy_image(game->mlx_ptr, game->p);
	mlx_destroy_window(game->mlx_ptr, game->mlx_win);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
}

int	exit_game(t_game *game)
{
	free_matrix(game);
	free_game(game);
	ft_putstr(KBLU"Window closed by user\n"KNRM);
	exit (0);
}
