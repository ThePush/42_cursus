/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_trim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:14:13 by jsemel            #+#    #+#             */
/*   Updated: 2022/04/06 16:49:31 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_quotes(char const *arg)
{
	int	count;
	int	i;
	int	d_quote;
	int	s_quote;

	i = 0;
	count = 0;
	d_quote = 0;
	s_quote = 0;
	while (arg && arg[i])
	{
		s_quote = (s_quote + (!d_quote && arg[i] == '\'')) % 2;
		d_quote = (d_quote + (!s_quote && arg[i] == '\"')) % 2;
		if ((arg[i] == '\"' && !s_quote) || (arg[i] == '\'' && !d_quote))
			count++;
		i++;
	}
	if (s_quote || d_quote)
		return (-1);
	return (count);
}

static char	*quotes_trim_util(char const *arg, int s_quote, int d_quote)
{
	int		count;
	int		i[2];
	char	*trimmed;

	i[1] = -1;
	i[0] = 0;
	count = count_quotes(arg);
	if (!arg || count == -1)
		return (NULL);
	trimmed = malloc(sizeof(char) * (ft_strlen(arg) - count + 1));
	if (!trimmed)
		return (NULL);
	while (arg[i[0]])
	{
		s_quote = (s_quote + (!d_quote && arg[i[0]] == '\'')) % 2;
		d_quote = (d_quote + (!s_quote && arg[i[0]] == '\"')) % 2;
		if ((arg[i[0]] != '\"' || s_quote) && (arg[i[0]] != '\'' || d_quote) \
			&& ++i[1] >= 0)
			trimmed[i[1]] = arg[i[0]];
		i[0]++;
	}
	trimmed[++i[1]] = '\0';
	return (trimmed);
}

char	**quotes_trim(char **args)
{
	char	**arr_tmp;
	char	*str_tmp;
	int		i;

	i = -1;
	arr_tmp = ft_dup_2d_array(args);
	while (arr_tmp && arr_tmp[++i])
	{
		str_tmp = quotes_trim_util(arr_tmp[i], 0, 0);
		free(arr_tmp[i]);
		arr_tmp[i] = str_tmp;
	}
	return (arr_tmp);
}
