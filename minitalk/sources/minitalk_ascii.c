/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_ascii.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 23:29:49 by jsemel            #+#    #+#             */
/*   Updated: 2022/01/04 03:49:01 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	print_ascii(void)
{
	ft_putendl_fd(KGRN"          _       _ _        _ _", 1);
	ft_putendl_fd(KGRN"    /\\/\\ (_)_ __ (_) |_ __ _| | | __", 1);
	ft_putendl_fd(KGRN"   /    \\| | '_ \\| | __/ _` | | |/ /", 1);
	ft_putendl_fd(KGRN"  / /\\/\\ \\ | | | | | || \(_| | |   <", 1);
	ft_putendl_fd(KGRN"  \\/    \\/_|_| |_|_|\\__\\__,_|_|_|\\_\\\n", 1);
	ft_putendl_fd(KGRN"      -------------------------     ", 1);
	ft_putendl_fd(KGRN"       A data exchange program", 1);
	ft_putendl_fd(KGRN"         using UNIX signals", 1);
	ft_putendl_fd(KGRN"      -------------------------     \n", 1);
	ft_putendl_fd(KGRN" -----------------------------------", 1);
	ft_printf(KGRN"   Opened server with PID ["KNRM);
	ft_printf(KMAG"%d"KNRM, getpid());
	ft_printf(KGRN"]\n"KNRM);
	ft_putendl_fd(KGRN" -----------------------------------", 1);
	ft_putendl_fd(KGRN"        --= INSTRUCTIONS =--", 1);
	ft_putendl_fd(KGRN"    Open a new terminal and run :\n", 1);
	ft_printf(KMAG"   ./client %d \"your_message\"\n\n", getpid());
	ft_printf(KGRN" Press [CTRL+C] to close this server\n");
	ft_putendl_fd(KGRN" -----------------------------------\n", 1);
}
