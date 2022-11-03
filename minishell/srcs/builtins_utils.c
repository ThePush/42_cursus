/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:29:56 by jsemel            #+#    #+#             */
/*   Updated: 2022/04/19 17:35:51 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

/*
** Always have an exit code > 0 and < 256 in ft_exit
*/
int	exit_status_handler(long status)
{
	status %= 256;
	while (status < 0)
		status += 256;
	return (status);
}

/*
** Check valid '-n' option for ft_echo
*/
bool	check_echo_opt(char *opt)
{
	int	i;

	i = 0;
	if (opt[0] == '-')
	{
		while (opt[++i])
		{
			if (opt[i] != 'n')
				return (false);
		}
		return (true);
	}
	return (false);
}
