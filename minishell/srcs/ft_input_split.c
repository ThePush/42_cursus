/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:11:39 by jsemel            #+#    #+#             */
/*   Updated: 2022/04/06 16:35:55 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_count_words(const char *inpt, char *set, int i[2])
{
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	while (inpt[i[0]] != '\0')
	{
		if (!ft_strchr(set, inpt[i[0]]))
		{
			i[1]++;
			while ((!ft_strchr(set, inpt[i[0]]) || q[0]) && inpt[i[0]] != '\0')
			{
				if (!q[1] && (inpt[i[0]] == '\"' || inpt[i[0]] == '\''))
					q[1] = inpt[i[0]];
				q[0] = (q[0] + (inpt[i[0]] == q[1])) % 2;
				q[1] *= q[0] != 0;
				i[0]++;
			}
			if (q[0])
				return (-1);
		}
		else
			i[0]++;
	}
	return (i[1]);
}

static char	**ft_fill_array(char **tmp, char const *input, char *set, int i[3])
{
	int		s_len;
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	s_len = ft_strlen(input);
	while (input[i[0]])
	{
		while (ft_strchr(set, input[i[0]]) && input[i[0]] != '\0')
			i[0]++;
		i[1] = i[0];
		while ((!ft_strchr(set, input[i[0]]) || q[0] || q[1]) && input[i[0]])
		{
			q[0] = (q[0] + (!q[1] && input[i[0]] == '\'')) % 2;
			q[1] = (q[1] + (!q[0] && input[i[0]] == '\"')) % 2;
			i[0]++;
		}
		if (i[1] >= s_len)
			tmp[i[2]++] = "\0";
		else
			tmp[i[2]++] = ft_substr(input, i[1], i[0] - i[1]);
	}
	return (tmp);
}

/*
** Split input on spaces taking quotes into account
*/
char	**ft_input_split(char const *input, char *set)
{
	char	**temp;
	int		words;
	int		i[3];
	int		counts[2];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	counts[0] = 0;
	counts[1] = 0;
	if (!input)
		return (NULL);
	words = ft_count_words(input, set, counts);
	if (words == -1)
		return (NULL);
	temp = malloc((words + 1) * sizeof(char *));
	if (temp == NULL)
		return (NULL);
	temp = ft_fill_array(temp, input, set, i);
	temp[words] = NULL;
	return (temp);
}
