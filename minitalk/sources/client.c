/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:48:13 by jsemel            #+#    #+#             */
/*   Updated: 2022/06/15 10:00:24 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static	t_infos g_infos;

static void	kill_to_server(int signum, int pid)
{
	if (kill(pid, signum) == -1)
		ft_error(TOSERVER);
}

static void	kill_null(int pid)
{
	size_t	i;

	i = 0;
	while (i <= CHAR_BITS)
	{
		kill_to_server(SIGUSR1, pid);
		usleep(500);
		i++;
	}
}

static void	handle_char_to_binary(int pid, char *str)
{
	size_t	i;
	int		shift;

	i = 0;
	while (str[i])
	{
		shift = CHAR_BITS;
		while (shift >= 0)
		{
			if ((str[i] & (1 << shift)))
				kill_to_server(SIGUSR2, pid);
			else
				kill_to_server(SIGUSR1, pid);
			usleep(1000);
			shift--;
		}
		i++;
	}
	kill_null(pid);
}

static void	signal_handler(int signum)
{
	static bool	boolean = true;

	if (signum == SIGUSR1 && boolean)
	{
		ft_printf(KGRN"=== Server ["KNRM);
		ft_printf(KMAG"%d"KNRM, g_infos.pid);
		ft_printf(KGRN"] receiving message... ===\n"KNRM);
		boolean = false;
	}
	if (signum == SIGUSR2)
	{
		ft_printf(KGRN"=== Server [", KNRM);
		ft_printf(KMAG"%d"KNRM, g_infos.pid);
		ft_printf(KGRN"] acknowledged message ===\n"KNRM);
		boolean = true;
		exit (EXIT_SUCCESS);
	}
}

int	main(int ac, char **av)
{
	if (ac == 3 && ft_str_digit(av[1]))
	{
		signal(SIGUSR1, signal_handler);
		signal(SIGUSR2, signal_handler);
		g_infos.pid = ft_atoi(av[1]);
		handle_char_to_binary(ft_atoi(av[1]), av[2]);
		while (true)
			pause();
	}
	else
		ft_error(ARGSFORMAT);
}
