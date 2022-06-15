/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 15:53:25 by jsemel            #+#    #+#             */
/*   Updated: 2022/06/15 09:59:22 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	ft_error(int error)
{
	if (error == TOSERVER)
	{
		ft_printf(KRED"=== Error | Could not send signal to server ===\n");
		ft_printf(KGRN"=== Check |           [PID_number]          ===\n");
	}
	else if (error == ARGSFORMAT)
	{
		ft_putendl_fd(KRED"=== Error   | Wrong format of arguments ===", 2);
		ft_putendl_fd(KGRN"=== Format  |  ./client [PID] \"message\" ===", 2);
	}
	else if (error == TOCLIENT)
	{
		ft_printf(KRED"=== Error encountered while");
		ft_putendl_fd(" sending signal to client ==="KNRM, 2);
	}
	else if (error == ALLOC)
		ft_putendl_fd(KRED"=== Heap memory allocation error ==="KNRM, 2);
	else if (error == NOARGS)
	{
		ft_putendl_fd(KRED"== Error | No argument needed ==="KNRM, 2);
		ft_putendl_fd(KGRN"== Usage |     ./server       ==="KNRM, 2);
	}
	exit (EXIT_FAILURE);
}
