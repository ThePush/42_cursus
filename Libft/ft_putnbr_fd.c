/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:50:51 by jsemel            #+#    #+#             */
/*   Updated: 2021/11/26 13:01:42 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nb = -n;
	}
	else
		nb = n;
	if (nb > 9)
	{
		ft_putnbr_fd((nb / 10), fd);
	}
	nb = nb % 10 + 48;
	ft_putchar_fd(nb, fd);
}
