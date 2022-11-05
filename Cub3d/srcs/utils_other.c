/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:31:51 by dpaccagn          #+#    #+#             */
/*   Updated: 2022/06/01 15:22:30 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_realloc_protected(void **ptr, size_t orig_size, size_t new_size)
{
	*ptr = ft_realloc(*ptr, orig_size, new_size);
	if (*ptr == 0)
		exit(EXIT_SUCCESS);
}

int	cub_next_line(int fd, char **line)
{
	char	buf;
	int		i;

	if (read(fd, 0, 0) == -1)
		return (-1);
	*line = malloc(MAX_LINE);
	if (!*line)
		return (-1);
	i = 0;
	while (read(fd, &buf, 1))
	{
		if (buf == '\n')
		{
			(*line)[i] = '\0';
			return (1);
		}
		(*line)[i++] = buf;
	}
	(*line)[i] = '\0';
	return (0);
}

void	ft_perror(char *str)
{
	ft_putendl_fd(KRED"Error", 2);
	ft_putendl_fd(str, 2);
}

void	ft_usage(char *str)
{
	ft_putendl_fd(KGRN"Usage", 1);
	ft_putendl_fd(str, 1);
}
