/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:47:11 by jsemel            #+#    #+#             */
/*   Updated: 2022/06/15 10:04:01 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static t_infos g_char;

static void	global_init(void)
{
	g_char.c = 0;
	g_char.bits = CHAR_BITS;
}

static char	*print_string(char *str)
{
	ft_printf(KGRN"\nPID ["KNRM);
	ft_printf(KMAG"%d", g_char.pid);
	ft_printf(KGRN"] >> "KNRM);
	if (!str)
		ft_printf("\n"KNRM);
	else
		ft_printf("%s\n"KNRM, str);
	free(g_char.str);
	return (NULL);
}

static void	kill_to_client(int signum)
{
	if (kill(g_char.pid, signum) == -1)
		ft_error(TOCLIENT);
}

static void	handle_bits_to_char(int signum, siginfo_t *siginfo, void *context)
{
	int	bit;

	(void)context;
	if ((siginfo)->si_pid)
		g_char.pid = siginfo->si_pid;
	if (signum == SIGUSR1)
		bit = 0;
	else
		bit = 1;
	g_char.c += bit << g_char.bits;
	g_char.bits--;
	if (g_char.bits == -1)
	{
		if (!g_char.c)
		{
			g_char.str = print_string(g_char.str);
			kill_to_client(SIGUSR2);
		}
		else
			g_char.str = ft_append_char(g_char.str, g_char.c);
		global_init();
	}
	kill_to_client(SIGUSR1);
}

int	main(int ac, char **av)
{
	(void)av;
	struct sigaction	sa;
	if (ac != 1)
		ft_error(NOARGS);
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_bits_to_char;
	global_init();
	g_char.str = NULL;
	print_ascii();
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (true)
		pause();
}
