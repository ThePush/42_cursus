/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:56:48 by jsemel            #+#    #+#             */
/*   Updated: 2022/04/22 10:40:36 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** var: PWD/SHLVL/PATH/_
** returns variable value or NULL if variable has not been found
*/
char	*ft_getenv(char *var, char **env, int len)
{
	int	i;
	int	n;

	i = 0;
	if (len < 0)
		len = ft_strlen(var);
	while (!ft_strchr(var, '=') && env && env[i])
	{
		n = len;
		if (n < ft_strchr_i(env[i], '='))
			n = ft_strchr_i(env[i], '=');
		if (!ft_strncmp(env[i], var, n))
			return (ft_substr(env[i], n + 1, ft_strlen(env[i])));
		i++;
	}
	return (NULL);
}

/*
** Checks if variable already exists,
** if it does overwrite it,
** else add a new row to the environment
*/

char	**ft_setenv(char *var, char *value, char **env, int len)
{
	int		i[2];
	char	*tmp[2];

	if (len < 0)
		len = ft_strlen(var);
	i[0] = -1;
	tmp[0] = ft_strjoin(var, "=");
	tmp[1] = ft_strjoin(tmp[0], value);
	free(tmp[0]);
	while (!ft_strchr(var, '=') && env && env[++i[0]])
	{
		i[1] = len;
		if (i[1] < ft_strchr_i(env[i[0]], '='))
			i[1] = ft_strchr_i(env[i[0]], '=');
		if (!ft_strncmp(env[i[0]], var, i[1]))
		{
			tmp[0] = env[i[0]];
			env[i[0]] = tmp[1];
			free(tmp[0]);
			return (env);
		}
	}
	env = ft_extend_2d_arr(env, tmp[1]);
	free(tmp[1]);
	return (env);
}

/*
** SHLVL is reset to 1 if > 999
*/
char	*shlvl_handler(t_prompt prompt)
{
	char	*val;
	char	*shlvl;
	int		nb;

	nb = 0;
	val = ft_getenv("SHLVL", prompt.env, 5);
	if (val)
		nb = ft_atoi(val);
	if (!val || ft_atoi(val) <= 0)
		shlvl = ft_strdup("1");
	if (nb >= 999)
	{
		shlvl = ft_itoa(1);
		ft_putstr_fd("minishell : warning: shell level ", 2);
		ft_putnbr_fd(nb + 1, 2);
		ft_putstr_fd(" too high, resetting to 1\n", 2);
	}
	else
	{
		if (val)
			shlvl = ft_itoa(ft_atoi(val) + 1);
	}
	free(val);
	return (shlvl);
}

/*
** Use ft_setenv and ft_getenv alternatively to create a functional environment
*/
t_prompt	init_env(t_prompt prompt, char *val, char **av)
{
	char	*shlvl;
	char	**tmp;

	val = getcwd(NULL, 0);
	tmp = ft_setenv("PWD", val, prompt.env, 3);
	prompt.env = ft_dup_2d_array(tmp);
	ft_free_2d_array(&tmp);
	free(val);
	shlvl = shlvl_handler(prompt);
	tmp = ft_setenv("SHLVL", shlvl, prompt.env, 5);
	prompt.env = ft_dup_2d_array(tmp);
	ft_free_2d_array(&tmp);
	free(shlvl);
	val = ft_getenv("PATH", prompt.env, 4);
	if (!val)
		prompt.env = ft_setenv("PATH", \
		"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", prompt.env, 4);
	free(val);
	val = ft_getenv("_", prompt.env, 1);
	if (!val)
		prompt.env = ft_setenv("_", av[0], prompt.env, 1);
	free(val);
	return (prompt);
}
