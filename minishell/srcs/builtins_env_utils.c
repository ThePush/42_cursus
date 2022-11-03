/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 18:06:56 by jsemel            #+#    #+#             */
/*   Updated: 2022/04/19 17:31:28 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	join_vars(t_prompt *prompt, char **av, int *i, char *tmp3)
{
	char	*tmp;
	char	*tmp2;
	int		pos_egal;

	tmp = ft_strdup(prompt->env[i[1]]);
	free(prompt->env[i[1]]);
	pos_egal = ft_strchars_i(av[i[0]], "=");
	tmp2 = ft_substr(av[i[0]], pos_egal + 1, ft_strlen(av[i[0]]));
	prompt->env[i[1]] = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	free(tmp3);
}

/*
** Checks if variable to set/unset exists and if string has a '=' in it
*/
int	var_in_env(char *av, char **env, int i[2])
{
	int	pos;

	i[1] = 0;
	pos = ft_strchr_i(av, '=');
	if (pos == -1)
		return (-1);
	while (env[i[1]])
	{
		if (!ft_strncmp(env[i[1]], av, pos + 1))
			return (1);
		i[1]++;
	}
	return (0);
}

bool	parse_var(char *av, char *function_name, int flag)
{
	int	i;

	i = ft_strchars_i(av, "=");
	if ((flag && !ft_str_check_var(av, i))
		|| (!flag && !ft_str_check_var(av, i - 1))
		|| (flag == 2 && !ft_str_check_var(av, -1)))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(function_name, 2);
		ft_putstr_fd(": `", 2);
		ft_putstr_fd(av, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (false);
	}
	return (true);
}
