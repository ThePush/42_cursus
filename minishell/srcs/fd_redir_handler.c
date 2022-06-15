/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redir_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:17:09 by jsemel            #+#    #+#             */
/*   Updated: 2022/04/28 00:07:30 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

/*
** Core function of the redirections
** oldfd is the infile/outfile parameter of the t_mini node which is going
** to be updated with a fd
** path is the destination of the redirection
** flags will dispatch the actions to be done according to the redirection type
** open() returns -1 on error
*/
static int	fd_handler(int oldfd, char *path, int flags[2])
{
	int			fd;
	struct stat	path_stat;

	fd = 0;
	stat(path, &path_stat);
	if (oldfd > 2)
		close(oldfd);
	if (!path)
		return (-1);
	if (access(path, F_OK) == -1 && !flags[0])
		ft_perror(NDIR, path, 127);
	else if (!flags[0] && access(path, R_OK) == -1)
		ft_perror(NPERM, path, 126);
	if (flags[0] && flags[1])
		fd = fd_handler_append(fd, path, path_stat);
	else if (flags[0] && !flags[1])
		fd = fd_handler_truncate(fd, path, path_stat);
	else if (!flags[0] && oldfd != -1)
		fd = open(path, O_RDONLY);
	else
		fd = oldfd;
	return (fd);
}

/*
** [>]
*/
t_mini	*redir_truncate(t_mini *node, char **args, int *i)
{
	int	flags[2];

	flags[0] = 1;
	flags[1] = 0;
	(*i)++;
	if (args[*i])
		node->outfile = fd_handler(node->outfile, args[*i], flags);
	if (!args[*i] || node->outfile == -1)
	{
		*i = -1;
		if (node->outfile != -1)
		{
			ft_perror(NLERR, NULL, 1);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (node);
}

/*
** [>>]
*/
t_mini	*redir_append(t_mini *node, char **args, int *i)
{
	int	flags[2];

	flags[0] = 1;
	flags[1] = 1;
	(*i)++;
	if (args[++(*i)])
		node->outfile = fd_handler(node->outfile, args[*i], flags);
	if (!args[*i] || node->outfile == -1)
	{
		*i = -1;
		if (node->outfile != -1)
		{
			ft_perror(NLERR, NULL, 1);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (node);
}

/*
** [<]
*/
t_mini	*redir_input(t_mini *node, char **args, int *i)
{
	int	flags[2];

	flags[0] = 0;
	flags[1] = 0;
	(*i)++;
	if (args[*i])
		node->infile = fd_handler(node->infile, args[*i], flags);
	if (!args[*i] || node->infile == -1)
	{
		*i = -1;
		if (node->infile != -1)
		{
			ft_perror(NLERR, NULL, 1);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (node);
}

/*
** [<<]
*/
t_mini	*redir_heredoc(t_mini *node, char **args, int *i, t_prompt *p)
{
	char	*tmp[2];
	char	*str[2];

	str[0] = NULL;
	str[1] = NULL;
	tmp[0] = NULL;
	tmp[1] = "minishell: warning: here-document delimited by end-of-file";
	(*i)++;
	if (args[++(*i)])
	{
		tmp[0] = args[*i];
		node->infile = get_here_doc(str, tmp, p);
	}
	if (!args[*i] || node->infile == -1)
	{
		*i = -1;
		if (node->infile != -1)
		{
			ft_perror(NLERR, NULL, 1);
			g_status = 2;
		}
	}
	return (node);
}
