/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pop_charset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 11:26:47 by jsemel            #+#    #+#             */
/*   Updated: 2022/04/19 17:33:23 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	ft_isin(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (true);
		i++;
	}
	return (false);
}

/*
** pop a charset from a string
*/
char	*ft_pop_charset(char *str, char *charset)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = malloc(ft_strlen(str));
	if (!tmp)
		return (NULL);
	while (str[i])
	{
		if (!ft_isin(str[i], charset))
		{
			tmp[j] = str[i];
			i++;
			j++;
		}
		else
			i++;
	}
	tmp[j] = '\0';
	return (tmp);
}
