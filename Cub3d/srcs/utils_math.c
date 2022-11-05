/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaccagn <dpaccagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:32:04 by dpaccagn          #+#    #+#             */
/*   Updated: 2022/06/01 14:34:50 by dpaccagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_split(char **split)
{
	while (*split)
		free(*split++);
}

double	rad_to_deg(double radian)
{
	return (radian * 180.0 / M_PI);
}

double	deg_to_rad(double degree)
{
	return (degree * M_PI / 180.0);
}

double	modulo_radian(double radian)
{
	double	circle;

	circle = deg_to_rad(360);
	radian = fmod(radian, circle);
	if (radian < 0)
		radian += circle;
	return (radian);
}

int	create_argb(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}
