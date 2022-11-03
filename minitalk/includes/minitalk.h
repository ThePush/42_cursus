/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:53:05 by jsemel            #+#    #+#             */
/*   Updated: 2022/06/15 09:58:09 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

// Libraries
# include <sys/types.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include "libft.h"

// TERMINAL MESSAGES COLORS
# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m" 
// Constants
# define CHAR_BITS 7
# define TOSERVER 1
# define ARGSFORMAT 2
# define TOCLIENT 3
# define ALLOC 4
# define NOARGS 5

// Structures
typedef struct s_infos
{
	char	c;
	int		bits;
	char	*str;
	int		pid;
}	t_infos;

// Minitalk print ASCII Art function
void	print_ascii(void);
// Minitalk utils functions
void	ft_error(int error);

#endif
