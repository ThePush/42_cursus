/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dimi <Dimi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:11:39 by dpaccagn          #+#    #+#             */
/*   Updated: 2021/11/28 00:26:22 by Dimi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buff;

	buff = malloc(size * nmemb);
	if (!buff)
		return (NULL);
	ft_bzero(buff, (nmemb * size));
	return (buff);
}

/* **************************************************************************
The calloc function is similar to malloc, but instead of only allocating me-
mory, it does fill it with zeroes
°************************************************************************** */
