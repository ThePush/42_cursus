/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaccagn <dpaccagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:48:46 by dpaccagn          #+#    #+#             */
/*   Updated: 2022/06/01 15:20:31 by dpaccagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**dup_map(int fd, char *line, int *height)
{
	char	**split;
	int		i;

	i = 0;
	split = malloc(sizeof(char *));
	if (!split)
		exit(EXIT_FAILURE);
	while (1)
	{
		split = ft_realloc(split,
				(i + 1) * sizeof(char *),
				(i + 2) * sizeof(char *));
		if (!split)
			exit(EXIT_FAILURE);
		split[i++] = ft_strdup(line);
		free(line);
		if (!cub_next_line(fd, &line) && *line == 0)
			break ;
	}
	free(line);
	split[i] = 0;
	*height = i;
	return (split);
}

static size_t	width_size(char **split)
{
	size_t	max_length;
	size_t	length;
	int		i;
	int		j;

	max_length = 0;
	i = 0;
	while (split[i])
	{
		length = 0;
		j = 0;
		while (split[i][j])
		{
			if (split[i][j] == '\t')
				length += 4;
			else
				length++;
			j++;
		}
		if (length > max_length)
			max_length = length;
		i++;
	}
	return (max_length);
}

static void	tabs_to_spaces_util(char **s, int width, int i[5])
{
	i[3] = width - i[2] + 1;
	ft_realloc_protected((void **)&s[i[0]], i[2] + 1, width + i[3]);
	while (i[3]--)
		s[i[0]][i[4]--] = ' ';
}

static char	**tabs_to_spaces(char **s, int width, int height)
{
	int	i[5];

	i[0] = -1;
	while (++i[0] < height)
	{
		i[1] = -1;
		i[2] = ft_strlen(s[i[0]]);
		i[4] = width;
		if (i[2] < i[4])
			tabs_to_spaces_util(s, width, i);
		while (++i[1] < width)
		{
			if (s[i[0]][i[1]] == '\t')
			{
				ft_memmove(&s[i[0]][i[1] + 4],
					&s[i[0]][i[1] + 1], i[2] - i[1] + 2);
				ft_strncpy(&s[i[0]][i[1]], "    ", 4);
				i[2] += 4;
			}
		}
		s[i[0]][i[1]] = '\0';
	}
	return (s);
}

void	parse_map(int fd, char *line, t_map *map)
{
	map->matrix = dup_map(fd, line, &map->height);
	map->width = width_size(map->matrix);
	map->matrix = tabs_to_spaces(map->matrix, map->width, map->height);
}
