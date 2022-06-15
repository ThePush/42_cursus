/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 10:41:14 by jsemel            #+#    #+#             */
/*   Updated: 2022/02/07 15:54:10 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define BUFFER_SIZE 1024

/*----------------------------------------------------------------------------
 * 3/
 * Cuts the line that has been sent to gnl from the buffer to update it
 * --------------------------------------------------------------------------*/
static char	*update_buff(char *buff)
{
	size_t	i;
	size_t	j;
	char	*newbuff;

	i = 0;
	j = 0;
	while ((buff[i] != '\n') && (buff[i] != '\0'))
		i++;
	if (!buff[i])
	{
		free(buff);
		return (NULL);
	}
	newbuff = malloc((ft_strlen(buff) - i + 1) * sizeof(char));
	if (!newbuff)
		return (NULL);
	while (buff[++i] != '\0')
		newbuff[j++] = buff[i];
	newbuff[j] = '\0';
	free(buff);
	return (newbuff);
}

/* --------------------------------------------------------------------------
 * 2/
 * Creates the line to return and copies the buffer in it, newline included
 *--------------------------------------------------------------------------*/

static char	*get_line(char *buff)
{
	char		*line;
	size_t		i;

	i = 0;
	if (!*buff)
		return (NULL);
	while ((buff[i] != '\n') && (buff[i] != '\0'))
		i++;
	line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	line = ft_strncpy(line, buff, i + 1);
	return (line);
}

/*----------------------------------------------------------------------------
 * 1/
 * Loads the static variable buffer[fd] with the fd content: concatenes until
 * a newline is found
 * or index == 0 
 *---------------------------------------------------------------------------*/

static char	*load_buffer(int fd, char *buffer)
{
	char	*tmp_buff;
	int		index_buff;

	index_buff = 1;
	tmp_buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp_buff)
		return (NULL);
	while ((!ft_strchr(buffer, '\n')) && (index_buff))
	{
		index_buff = read(fd, tmp_buff, BUFFER_SIZE);
		if (index_buff == -1)
		{
			free(tmp_buff);
			return (NULL);
		}
		tmp_buff[index_buff] = '\0';
		buffer = ft_strjoin_gnl(buffer, tmp_buff);
	}
	free(tmp_buff);
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer[1024];

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer[fd] = load_buffer(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = get_line(buffer[fd]);
	buffer[fd] = update_buff(buffer[fd]);
	return (line);
}
