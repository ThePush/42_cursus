/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 21:39:22 by jsemel            #+#    #+#             */
/*   Updated: 2022/04/18 21:39:53 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Joins str and var where var is the home path
*/
char	*expand_path(char *arg, int i, int quotes[2], char *var)
{
	char	*path;
	char	*tmp;

	quotes[0] = 0;
	quotes[1] = 0;
	while (arg && arg[++i])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && arg[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && arg[i] == '\"')) % 2;
		if (!quotes[0] && !quotes[1] && arg[i] == '~' && (i == 0 || \
			arg[i - 1] != '$'))
		{
			tmp = ft_substr(arg, 0, i);
			path = ft_strjoin(tmp, var);
			free(tmp);
			tmp = ft_substr(arg, i + 1, ft_strlen(arg));
			free(arg);
			arg = ft_strjoin(path, tmp);
			free(tmp);
			free(path);
			return (expand_path(arg, i + ft_strlen(var) - 1, quotes, var));
		}
	}
	free(var);
	return (arg);
}
