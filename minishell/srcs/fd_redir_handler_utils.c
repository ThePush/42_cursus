/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redir_handler_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 14:31:02 by dimioui           #+#    #+#             */
/*   Updated: 2022/04/26 14:36:26 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	fd_handler_truncate(int fd, char *path, struct stat path_stat)
{
	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd == -1 && S_ISDIR(path_stat.st_mode))
		ft_perror(IS_DIR, path, 127);
	else if (fd == -1 && access(path, W_OK) == -1 && access(path, F_OK) == 0)
		ft_perror(NPERM, path, 126);
	return (fd);
}

int	fd_handler_append(int fd, char *path, struct stat path_stat)
{
	fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd == -1 && S_ISDIR(path_stat.st_mode))
		ft_perror(IS_DIR, path, 127);
	else if (fd == -1 && access(path, W_OK) == -1 && access(path, F_OK) == 0)
		ft_perror(NPERM, path, 126);
	return (fd);
}
