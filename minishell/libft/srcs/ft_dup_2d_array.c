/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:14:04 by dimioui           #+#    #+#             */
/*   Updated: 2022/04/06 11:32:38 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dup_2d_array(char **a)
{
	char	**arr;
	int		rows;
	int		i;

	i = 0;
	rows = ft_2d_arr_len(a);
	arr = malloc(sizeof(char *) * (rows + 1));
	if (!arr)
		return (NULL);
	while (a[i])
	{
		arr[i] = ft_strdup(a[i]);
		if (!arr[i])
		{
			ft_free_2d_array(&arr);
			return (NULL);
		}
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
