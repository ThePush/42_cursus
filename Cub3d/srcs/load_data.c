/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaccagn <dpaccagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:36:17 by dpaccagn          #+#    #+#             */
/*   Updated: 2022/06/01 14:36:46 by dpaccagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_texture(char *texture_path, t_texture *texture)
{
	if (!texture->path)
		texture->path = ft_strdup(texture_path);
	else
		texture->path = 0;
}

static void	get_color(char *str, t_color *color)
{
	int		i;
	char	**split;

	if (color->r != -1)
	{
		color->r = -1;
		return ;
	}
	if (ft_strchr_i(str, ',') != 2)
		return ;
	split = ft_symsplit(str, ",");
	if (!split)
		return ;
	i = 0;
	while (split[i] && ft_strisdigit(split[i]))
		i++;
	if (i == 3)
	{
		color->r = ft_atoi(split[0]);
		color->g = ft_atoi(split[1]);
		color->b = ft_atoi(split[2]);
	}
	free_split(split);
	free(split);
}

static void	get_elements(char **split, t_data *datas)
{
	if (split[0] == 0)
		return ;
	else if (!ft_strcmp(split[0], "NO") && split[1] != 0 && split[2] == 0)
		get_texture(split[1], &datas->no_xpm);
	else if (!ft_strcmp(split[0], "SO") && split[1] != 0 && split[2] == 0)
		get_texture(split[1], &datas->so_xpm);
	else if (!ft_strcmp(split[0], "WE") && split[1] != 0 && split[2] == 0)
		get_texture(split[1], &datas->we_xpm);
	else if (!ft_strcmp(split[0], "EA") && split[1] != 0 && split[2] == 0)
		get_texture(split[1], &datas->ea_xpm);
	else if (!ft_strcmp(split[0], "F") && split[1] != 0 && split[2] == 0)
		get_color(split[1], &datas->floor);
	else if (!ft_strcmp(split[0], "C") && split[1] != 0 && split[2] == 0)
		get_color(split[1], &datas->ceilling);
	else if (split[0][0] != '\n')
	{
		printf("Error\nUnknown identifier: %s\n", split[0]);
		exit(EXIT_FAILURE);
	}
	datas->res.width = RES_WIDTH;
	datas->res.height = RES_HEIGHT;
}

static bool	is_map(char *line)
{
	int	check;

	check = 0;
	while (*line)
	{
		if (!ft_strchr("01NSEW \n\t\v\f\r", *line))
			return (false);
		else if (*line == '1')
			check = 1;
		line++;
	}
	return (check);
}

void	load_data(int fd, t_data *datas)
{
	char	*line;
	char	**split;

	ft_memset(datas, 0, sizeof(t_data));
	ft_memset(&datas->floor, -1, sizeof(t_color));
	ft_memset(&datas->ceilling, -1, sizeof(t_color));
	line = 0;
	while (cub_next_line(fd, &line))
	{
		if (!is_map(line))
		{
			split = ft_symsplit(line, " \n\t\v\f\r");
			get_elements(split, datas);
			free_split(split);
			free(split);
			free(line);
		}
		else
			parse_map(fd, line, &datas->map);
	}
	free(line);
}
