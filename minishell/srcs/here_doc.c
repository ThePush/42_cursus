/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 09:50:26 by jsemel            #+#    #+#             */
/*   Updated: 2022/04/22 15:03:14 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

/*
** exit_code 130 = CTRL+C
*/
static char	*get_here_str(char *str[2], size_t len, char *limit, char *warn)
{
	char	*tmp;

	while (g_status != 130 && (!str[0] || ft_strncmp(str[0], limit, len) \
		|| ft_strlen(limit) != len))
	{
		tmp = str[1];
		str[1] = ft_strjoin(str[1], str[0]);
		free(tmp);
		free(str[0]);
		str[0] = readline("> ");
		if (!str[0])
		{
			printf("%s (wanted `%s\')\n", warn, limit);
			break ;
		}
		tmp = str[0];
		str[0] = ft_strjoin(str[0], "\n");
		free(tmp);
		len = ft_strlen(str[0]) - 1;
	}
	free(str[0]);
	return (str[1]);
}

static char	*expand_heredoc(char *str[2], t_prompt *p)
{
	char	**split;
	char	*tmp[2];
	int		quotes[2];
	int		i;

	i = -1;
	split = ft_split(str[1], '\n');
	free(str[1]);
	str[1] = NULL;
	str[0] = NULL;
	while (split[++i])
	{
		tmp[0] = expand_vars(split[i], -1, quotes, p);
		tmp[1] = str[0];
		str[0] = ft_strjoin(str[1], tmp[0]);
		free(tmp[1]);
		tmp[1] = str[1];
		str[1] = ft_strjoin(str[0], "\n");
		free(tmp[1]);
		free(str[0]);
		free(tmp[0]);
		str[0] = NULL;
	}
	free(split);
	return (str[1]);
}

/*
** Writes here_doc user input strings on write_end of the node (=infile)
** ex: cat << EOF > /tmp/yourfilehere
*/
int	get_here_doc(char *str[2], char *tmp[2], t_prompt *p)
{
	int		fd[2];

	g_status = 0;
	if (pipe(fd) == -1)
	{
		ft_perror(PIPERR, NULL, 1);
		return (-1);
	}
	str[1] = get_here_str(str, 0, tmp[0], tmp[1]);
	if (str[1])
		expand_heredoc(str, p);
	write(fd[WRITE_END], str[1], ft_strlen(str[1]));
	free(str[1]);
	close(fd[WRITE_END]);
	if (g_status == 130)
	{
		close(fd[READ_END]);
		return (-1);
	}
	return (fd[READ_END]);
}
