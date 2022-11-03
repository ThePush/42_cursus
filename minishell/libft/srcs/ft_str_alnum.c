/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_alnum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:50:57 by jsemel            #+#    #+#             */
/*   Updated: 2022/04/15 15:54:09 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_str_alnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
			return (false);
		i++;
	}
	return (true);
}
