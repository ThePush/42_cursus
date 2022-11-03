/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 11:40:31 by jsemel            #+#    #+#             */
/*   Updated: 2021/12/06 10:02:51 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

size_t	ft_strlen(char *str);

char	*ft_strchr(char *s, int c);

char	*ft_strjoin(char *s1, char *s2);

char	*ft_strncpy(char *dest, char *src, size_t n);

char	*get_next_line(int fd);

#endif
