/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 22:49:35 by jsemel            #+#    #+#             */
/*   Updated: 2021/11/24 15:25:53 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arr;

	arr = malloc((nmemb * size) * sizeof(void));
	if (!arr)
		return (NULL);
	ft_bzero(arr, (nmemb * size));
	return (arr);
}
