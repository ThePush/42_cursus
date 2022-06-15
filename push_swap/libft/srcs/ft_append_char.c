/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 17:20:37 by jsemel            #+#    #+#             */
/*   Updated: 2022/02/07 15:53:48 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*char_to_str(char c)
{
	char	*new_string;

	new_string = malloc(2 * sizeof(char));
	if (!new_string)
		return (NULL);
	new_string[0] = c;
	new_string[1] = '\0';
	return (new_string);
}

char	*ft_append_char(char *str, char c)
{
	size_t	i;
	char	*new_string;

	i = 0;
	if (!c)
		return (NULL);
	if (!str)
	{
		return (char_to_str(c));
	}
	new_string = malloc((ft_strlen(str) + 2) * sizeof(char));
	if (!new_string)
	{
		free(str);
		return (NULL);
	}
	while (str[i])
	{
		new_string[i] = str[i];
		i++;
	}
	free(str);
	new_string[i] = c;
	new_string[i + 1] = '\0';
	return (new_string);
}
