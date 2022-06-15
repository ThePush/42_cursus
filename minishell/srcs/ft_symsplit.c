/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_symsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimioui <dimioui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:03:15 by jsemel            #+#    #+#             */
/*   Updated: 2022/04/17 12:21:24 by dimioui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_count_words(char *a, char *set, int count)
{
	int		q[2];
	int		i;

	i = 0;
	q[0] = 0;
	q[1] = 0;
	while (a && a[i] != '\0')
	{
		count++;
		if (!ft_strchr(set, a[i]))
		{
			while ((!ft_strchr(set, a[i]) || q[0] || q[1]) && a[i] != '\0')
			{
				q[0] = (q[0] + (!q[1] && a[i] == '\'')) % 2;
				q[1] = (q[1] + (!q[0] && a[i] == '\"')) % 2;
				i++;
			}
			if (q[0] || q[1])
				return (-1);
		}
		else
			i++;
	}
	return (count);
}

static char	**ft_fill_array(char **splitted, char *args, char *set, int i[3])
{
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	while (args && args[i[0]] != '\0')
	{
		i[1] = i[0];
		if (!ft_strchr(set, args[i[0]]))
		{
			while ((!ft_strchr(set, args[i[0]]) || q[0] || q[1]) && args[i[0]])
			{
				q[0] = (q[0] + (!q[1] && args[i[0]] == '\'')) % 2;
				q[1] = (q[1] + (!q[0] && args[i[0]] == '\"')) % 2;
				i[0]++;
			}
		}
		else
			i[0]++;
		splitted[i[2]++] = ft_substr(args, i[1], i[0] - i[1]);
	}
	return (splitted);
}

/*
** Splits argument with "<|>" as delimiters
*/

char	**ft_symsplit(char const *args, char *set)
{
	char	**splitted_args;
	int		words;
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	if (!args)
		return (NULL);
	words = ft_count_words((char *)args, set, 0);
	if (words == -1)
		return (NULL);
	splitted_args = malloc((words + 1) * sizeof(char *));
	if (splitted_args == NULL)
		return (NULL);
	splitted_args = ft_fill_array(splitted_args, (char *)args, set, i);
	splitted_args[words] = NULL;
	return (splitted_args);
}
