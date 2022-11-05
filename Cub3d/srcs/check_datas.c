/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_datas.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:28:47 by jsemel            #+#    #+#             */
/*   Updated: 2022/06/01 15:24:38 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_xpm(t_data *datas, char *texture_path)
{
	if (!texture_path)
	{
		ft_perror("check_xpm(): At least one texture is missing");
		ft_usage("Please provide one path for each wall texture (NO/SO/EA/WE)");
		free_datas(datas);
		exit(EXIT_FAILURE);
	}
	if (!check_extension(texture_path, ".xpm"))
	{
		ft_perror("check_xpm(): Wrong texture extension");
		ft_usage("Textures should have .xpm extensions");
		free_datas(datas);
		exit(EXIT_FAILURE);
	}
}

static void	check_xpm_fd(t_data *datas, char *texture_path)
{
	int	fd;

	fd = open(texture_path, O_RDONLY);
	if (fd == -1)
	{
		ft_perror("check_xpm(): Could not open xpm");
		ft_usage("Check asset's path in .cub file");
		free_datas(datas);
		exit(EXIT_FAILURE);
	}
	if (close(fd) == -1)
	{
		ft_perror("check_xpm(): Could not close xpm");
		free_datas(datas);
		exit(EXIT_FAILURE);
	}
}

static void	check_color(t_data *datas, t_color *color, char *color_identifier)
{
	if (color->r == -1)
	{
		ft_perror("check_color(): Wrong color code on line:");
		ft_putendl_fd(color_identifier, 2);
		ft_usage("Please provide colors in rgb format (ex. 255,255,255)");
		free_datas(datas);
		exit(EXIT_FAILURE);
	}
	else if (color->r > 255 || color->g > 255 || color->b > 255)
	{
		ft_perror("check_color(): Wrong color code on line:");
		ft_putendl_fd(color_identifier, 2);
		ft_usage("r, g, b, min int is 0 and max int is 255");
		free_datas(datas);
		exit(EXIT_FAILURE);
	}
	color->argb = create_argb(0, color->r, color->g, color->b);
}

void	check_data(t_data *datas)
{
	check_xpm(datas, datas->no_xpm.path);
	check_xpm_fd(datas, datas->no_xpm.path);
	check_xpm(datas, datas->so_xpm.path);
	check_xpm_fd(datas, datas->so_xpm.path);
	check_xpm(datas, datas->we_xpm.path);
	check_xpm_fd(datas, datas->we_xpm.path);
	check_xpm(datas, datas->ea_xpm.path);
	check_xpm_fd(datas, datas->ea_xpm.path);
	check_color(datas, &datas->floor, "F (floor)");
	check_color(datas, &datas->ceilling, "C (ceilling)");
	check_map(datas);
	check_map2(datas);
}
