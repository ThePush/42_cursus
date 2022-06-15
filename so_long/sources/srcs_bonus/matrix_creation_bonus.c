/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 18:35:58 by jsemel            #+#    #+#             */
/*   Updated: 2021/12/20 11:09:59 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

char	**create_matrix(char *map_av)
{
	char	**created_matrix;
	char	*buff;
	char	*tmp_buff;
	char	*strmap;
	int		fd;

	fd = open(map_av, O_RDONLY);
	if (fd == -1)
		return (NULL);
	strmap = malloc(sizeof(char));
	strmap[0] = '\0';
	buff = get_next_line(fd);
	while (buff)
	{
		tmp_buff = strmap;
		strmap = ft_strjoin(tmp_buff, buff);
		free(buff);
		buff = get_next_line(fd);
	}
	created_matrix = ft_split(strmap, '\n');
	free(strmap);
	close(fd);
	return (created_matrix);
}
