/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:35:03 by jsemel            #+#    #+#             */
/*   Updated: 2022/06/01 14:35:04 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_game(t_game *game)
{
	free_datas(&game->datas);
	free(game->rays.arr);
}

void	free_datas(t_data *datas)
{
	free(datas->no_xpm.path);
	free(datas->so_xpm.path);
	free(datas->we_xpm.path);
	free(datas->ea_xpm.path);
	if (datas->map.matrix)
		free_map(&datas->map);
}

void	free_map(t_map *map)
{
	int	i;

	i = -1;
	if (!map)
		return ;
	while (++i < map->height)
	{
		free(map->matrix[i]);
	}
	free(map->matrix);
}
