/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:36:32 by jsemel            #+#    #+#             */
/*   Updated: 2022/04/26 13:25:06 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Export/update a variable in env if '+='
*/
static int	ft_export_join(t_prompt *prompt)
{
	int		i[3];
	char	**av;
	char	*tmp;

	av = ((t_mini *)prompt->cmds->content)->full_cmd;
	if (ft_2d_arr_len(av) >= 2 && parse_var(av[1], "export", 0))
	{
		i[0] = 1;
		while (av[i[0]])
		{
			tmp = ft_pop_charset(av[i[0]], "+");
			i[2] = var_in_env(tmp, prompt->env, i);
			if (i[2] == 1)
				join_vars(prompt, av, i, tmp);
			else if (!i[2])
			{
				prompt->env = ft_extend_2d_arr(prompt->env, tmp);
				free(tmp);
			}
			i[0]++;
		}
	}
	else
		return (1);
	return (0);
}

/*
** Checks if variable already exists,
** if it does overwrite it,
** else add a new row to the environment
*/
static int	ft_export_classic(t_prompt *prompt)
{
	int		i[2];
	int		pos;
	char	**av;

	av = ((t_mini *)prompt->cmds->content)->full_cmd;
	if (ft_2d_arr_len(av) >= 2)
	{
		i[0] = 1;
		while (av[i[0]])
		{
			if (parse_var(av[i[0]], "export", 1))
			{
				pos = var_in_env(av[i[0]], prompt->env, i);
				if (pos == 1)
				{
					free(prompt->env[i[1]]);
					prompt->env[i[1]] = ft_strdup(av[i[0]]);
				}
				else if (!pos)
					prompt->env = ft_extend_2d_arr(prompt->env, av[i[0]]);
			}
			i[0]++;
		}
	}
	else
		return (1);
	return (0);
}

/*
** Check wether we have to append a value to an existing variable or not
*/
int	ft_export(t_prompt *prompt)
{
	int		pos_egal;
	char	**av;

	av = ((t_mini *)prompt->cmds->content)->full_cmd;
	pos_egal = ft_strchars_i(av[1], "=");
	if ((pos_egal >= 2) && (av[1][pos_egal - 1] == '+'))
		return (ft_export_join(prompt));
	else
		return (ft_export_classic(prompt));
	return (1);
}

/*
** Add "=" to variable to search in env
** if found, set its line in environment to NULL
*/
int	ft_unset(t_prompt *prompt)
{
	char	**av;
	char	*tmp;
	int		i[2];

	i[0] = 0;
	av = ((t_mini *)prompt->cmds->content)->full_cmd;
	if (ft_2d_arr_len(av) >= 2 && parse_var(av[1], "unset", 2))
	{
		while (av[++i[0]])
		{
			if (av[i[0]][ft_strlen(av[i[0]]) - 1] != '=')
			{
				tmp = ft_strjoin(av[i[0]], "=");
				free(av[i[0]]);
				av[i[0]] = tmp;
			}
			if (var_in_env(av[i[0]], prompt->env, i))
				ft_arr_replace_in(&prompt->env, NULL, i[1]);
		}
	}
	else
		return (1);
	return (0);
}
