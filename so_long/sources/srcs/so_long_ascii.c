/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_ascii_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 00:11:35 by jsemel            #+#    #+#             */
/*   Updated: 2022/01/04 00:19:50 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	print_ascii(void)
{
	ft_putendl_fd(KGRN"               _", 1);
	ft_putendl_fd(KGRN"  ___  ___    | | ___  _ __   __ _ ", 1);
	ft_putendl_fd(KGRN" / __|/ _ \\   | |/ _ \\| '_ \\ / _` |", 1);
	ft_putendl_fd(KGRN" \\__ \\ (_) |  | | (_) | | | | (_| |", 1);
	ft_putendl_fd(KGRN" |___/\\___/___|_|\\___/|_| |_|\\__, |", 1);
	ft_putendl_fd(KGRN"                             |___/ ", 1);
	ft_putendl_fd(KNRM"", 1);
}
