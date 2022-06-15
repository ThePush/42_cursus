/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_replace_in.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:24:42 by dimioui           #+#    #+#             */
/*   Updated: 2022/04/06 11:34:01 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arr_replace_in(char ***big, char **small, int n)
{
	char	**tmp;
	int		i[3];

	i[0] = -1;
	i[1] = -1;
	i[2] = -1;
	if (!big || !*big || n < 0 || n >= ft_2d_arr_len(*big))
		return (NULL);
	tmp = ft_calloc(ft_2d_arr_len(*big) + ft_2d_arr_len(small), sizeof(char *));
	while (tmp && big[0][++i[0]])
	{
		if (i[0] != n)
			tmp[++i[2]] = ft_strdup(big[0][i[0]]);
		else
		{
			while (small && small[++i[1]])
				tmp[++i[2]] = ft_strdup(small[i[1]]);
		}
	}
	ft_free_2d_array(big);
	*big = tmp;
	return (*big);
}
