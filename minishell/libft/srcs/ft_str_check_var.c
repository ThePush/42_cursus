/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_check_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 16:51:27 by jsemel            #+#    #+#             */
/*   Updated: 2022/04/17 11:13:28 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Man bash:
** An env variable name must be a name[=word]
** name:
** A word consisting solely of letters, numbers, and underscores,
** 	and beginning with a letter or underscore
** pos: "="
*/
bool	ft_str_check_var(char *str, int pos)
{
	int	i;

	i = 0;
	if ((!ft_isalpha(str[i])) && (str[i] != '_'))
		return (false);
	if (pos == -1)
	{
		while (str[i])
		{
			if (!ft_isalnum(str[i]) && (str[i] != '_'))
				return (false);
			i++;
		}
	}
	else
	{
		while (str[i] && i < pos)
		{
			if (!ft_isalnum(str[i]) && (str[i] != '_'))
				return (false);
			i++;
		}
	}
	return (true);
}
