/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 21:40:10 by jsemel            #+#    #+#             */
/*   Updated: 2022/04/27 23:06:19 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

static void	init_substr(char *arg, int i, t_prompt *prompt, char *tmp[4])
{
	char	**tmp_split;

	tmp[0] = ft_substr(arg, 0, i - 1);
	tmp_split = ft_symsplit(&arg[i], "/~%^{}:;=+-*#.,[]@?\"\'");
	tmp[3] = ft_getenv(tmp_split[0], prompt->env, \
		ft_strchars_i(tmp_split[0], "\"\'$|>< "));
	ft_free_2d_array(&tmp_split);
	if (!tmp[3] && arg[i] == '$')
		tmp[3] = ft_itoa(prompt->pid);
	else if (!tmp[3] && arg[i] == '?')
		tmp[3] = ft_itoa(g_status);
}

static void	get_substr_var2(char *arg, int i, char *tmp[4], int j[2])
{
	tmp[2] = ft_strjoin(tmp[0], tmp[3]);
	free(tmp[0]);
	j[1] = ft_strchars_i(&arg[i - 1], "/~%^{}:;=+-*#.,[]@?\"\'");
	if (j[1] >= 0 && tmp[3])
	{
		tmp[1] = ft_strdup(&arg[j[1]
				+ (ft_strlen(tmp[2]) - ft_strlen(tmp[3]))]);
		tmp[0] = ft_strjoin(tmp[2], tmp[1]);
		free(tmp[1]);
	}
	else if (j[1] >= 0)
	{
		tmp[1] = ft_strdup(&arg[j[1] + ft_strlen(tmp[2])]);
		tmp[0] = ft_strjoin(tmp[2], tmp[1]);
		free(tmp[1]);
	}
	else
		tmp[0] = ft_strdup(tmp[2]);
	free(tmp[3]);
	free(tmp[2]);
	free(arg);
}

static char	*get_substr_var(char *arg, int i, t_prompt *prompt)
{
	char	*tmp[4];
	int		j[2];

	j[1] = -1;
	j[0] = ft_strchars_i(&arg[i], "|\"\'$?>< ") + (ft_strchr("$?", arg[i]) != 0);
	if (j[0] == -1)
		j[0] = ft_strlen(arg) - 1;
	init_substr(arg, i, prompt, tmp);
	if (j[0] == 1)
	{
		free(tmp[0]);
		free(arg);
		return (tmp[3]);
	}
	else
	{
		get_substr_var2(arg, i, tmp, j);
		return (tmp[0]);
	}
}

/*
** Takes non-trimmed words as argument
** Checks if quotes are even or uneven
*/
char	*expand_vars(char *arg, int i, int quotes[2], t_prompt *prompt)
{
	quotes[0] = 0;
	quotes[1] = 0;
	while (arg && arg[++i])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && arg[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && arg[i] == '\"')) % 2;
		if (!quotes[0] && arg[i] == '$' && arg[i + 1] && \
			((ft_strchars_i(&arg[i + 1], "/~%^{}:; ") && !quotes[1]) || \
			(ft_strchars_i(&arg[i + 1], "/~%^{}:;\"") && quotes[1])))
			return (expand_vars(get_substr_var(arg, ++i, prompt), -1, \
			quotes, prompt));
	}
	return (arg);
}
