/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 01:27:51 by jsemel            #+#    #+#             */
/*   Updated: 2022/04/26 13:21:04 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*update_buff(char *buf, char *line)
{
	char	*newbuf;
	int		line_len;

	if (!buf || !line)
		return (buf);
	line_len = ft_strlen(line);
	if ((int)ft_strlen(buf) == line_len)
	{
		free(buf);
		return (NULL);
	}
	newbuf = ft_substr(buf, line_len, ft_strlen(buf) - line_len);
	free(buf);
	return (newbuf);
}

char	*get_newline(int fd)
{
	char	*tmp;
	int		nbytes;

	tmp = malloc(100);
	if (!tmp)
		return (NULL);
	nbytes = read(fd, tmp, 100);
	if (nbytes < 0)
	{
		free(tmp);
		return (NULL);
	}
	tmp[nbytes] = '\0';
	return (tmp);
}

char	*expand_buffer(char *buf, int fd)
{
	char	*newbuf;
	int		newlen;
	char	*tmp;

	tmp = get_newline(fd);
	if (!tmp)
		return (NULL);
	if (!tmp[0])
	{
		free(tmp);
		return (buf);
	}
	if (!buf)
		return (tmp);
	newlen = ft_strlen(buf) + ft_strlen(tmp);
	newbuf = malloc(newlen + 1);
	if (!newbuf)
		return (NULL);
	ft_strlcpy(newbuf, buf, newlen + 1);
	ft_strlcat(newbuf, tmp, newlen + 1);
	free(buf);
	free(tmp);
	return (newbuf);
}

char	*get_next_line(int fd)
{
	static char	*buf[4096];
	char		*line;
	size_t		old_len;

	if (fd < 0 || fd > 4095)
		return (NULL);
	line = NULL;
	if (ft_strchr_i(buf[fd], '\n') == -1)
	{
		old_len = ft_strlen(buf[fd]);
		buf[fd] = expand_buffer(buf[fd], fd);
		if (old_len == ft_strlen(buf[fd]) && buf[fd])
			line = ft_substr(buf[fd], 0, ft_strlen(buf[fd]));
	}
	if (!buf[fd])
		return (NULL);
	if (!line && ft_strchr_i(buf[fd], '\n') != -1)
		line = ft_substr(buf[fd], 0, ft_strchr_i(buf[fd], '\n') + 1);
	if (line)
	{
		buf[fd] = update_buff(buf[fd], line);
		return (line);
	}
	return (get_next_line(fd));
}
