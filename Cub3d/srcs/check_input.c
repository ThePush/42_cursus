/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:33:37 by jsemel            #+#    #+#             */
/*   Updated: 2022/06/10 11:30:44 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_args(int ac, char **av)
{
	if ((ac == 2) && ft_strlen(av[1]) == 4)
	{
		ft_perror("check_args(): Map has no name");
		exit(EXIT_FAILURE);
	}
	else if ((ac == 2) && !check_extension(av[1], ".cub"))
	{
		ft_perror("check_args(): File has a wrong extension");
		exit(EXIT_FAILURE);
	}
	else if (ac == 2 && check_extension(av[1], ".cub"))
		return ;
	else
	{
		ft_perror("check_args(): Wrong number of arguments");
		exit(EXIT_FAILURE);
	}
}

bool	check_extension(char *file, char *extension)
{
	int	len_file;
	int	len_ext;

	len_file = ft_strlen(file);
	len_ext = ft_strlen(extension);
	if (len_file <= len_ext)
		return (false);
	else if (!ft_strncmp(&file[len_file - len_ext], extension, len_ext + 1))
		return (true);
	else
		return (false);
}
