/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_symsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaccagn <dpaccagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:40:33 by dimioui           #+#    #+#             */
/*   Updated: 2022/06/01 15:32:23 by dpaccagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_length(char *str, char *charset)
{
	int	count;

	count = 0;
	while (*str)
		if (!ft_strchr(charset, *str++))
			count++;
	return (count);
}

static void	import_str(char **dest, char *src, int start, int end)
{
	*dest = malloc(((end - start + 1) * sizeof(char)));
	if (!*dest)
		return ;
	ft_strncpy(*dest, src, end - start);
	(*dest)[end - start] = '\0';
}

char	**ft_symsplit(char *str, char *charset)
{
	char	**strs;
	int		i;
	int		j;
	int		k;

	j = 0;
	k = 0;
	if (str == 0)
		return (0);
	strs = malloc((find_length(str, charset) + 1) * sizeof(char *));
	if (!strs)
		return (0);
	while (str[j] != '\0')
	{
		i = j;
		while (!ft_strchr(charset, str[j]) && str[j] != '\0')
			j++;
		if (i != j)
			import_str(&strs[k++], &str[i], i, j);
		else
			j++;
	}
	strs[k] = 0;
	return (strs);
}
