/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extend_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:22:43 by dimioui           #+#    #+#             */
/*   Updated: 2022/04/06 11:36:50 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_extend_2d_arr(char **in, char *newstr)
{
	char	**out;
	int		len;
	int		i;

	i = -1;
	out = NULL;
	if (!newstr)
		return (in);
	len = ft_2d_arr_len(in);
	out = malloc(sizeof(char *) * (len + 2));
	out[len + 1] = NULL;
	if (!out)
		return (in);
	while (++i < len)
	{
		out[i] = ft_strdup(in[i]);
		if (!out[i])
		{
			ft_free_2d_array(&in);
			ft_free_2d_array(&out);
		}
	}
	out[i] = ft_strdup(newstr);
	ft_free_2d_array(&in);
	return (out);
}
