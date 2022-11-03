/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:22:01 by jsemel            #+#    #+#             */
/*   Updated: 2022/04/22 20:08:27 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

/*
** Exits and updates exit code with argument
*/
int	ft_exit(t_list *cmd, int *is_exit)
{
	t_mini	*node;
	long	status[2];

	node = cmd->content;
	*is_exit = !cmd->next;
	if (*is_exit)
		ft_putstr_fd("exit\n", 2);
	if (!node->full_cmd || !node->full_cmd[1])
		return (0);
	status[1] = ft_atoi2(node->full_cmd[1], &status[0]);
	if (status[1] == -1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(node->full_cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (2);
	}
	else if (node->full_cmd[2])
	{
		*is_exit = 0;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	status[0] = exit_status_handler(status[0]);
	return (status[0]);
}

/*
** Open the argument of cd command and execute chdir if possible
*/
static void	exec_cd(char **str[2])
{
	DIR			*dir;
	struct stat	path_stat;

	stat(str[0][1], &path_stat);
	dir = NULL;
	if (str[0][1])
		dir = opendir(str[0][1]);
	if (!str[0][1] && str[1][0] && !str[1][0][0])
	{
		g_status = 1;
		ft_putstr_fd("minishell: HOME not set\n", 2);
	}
	if (str[1][0] && !str[0][1])
		g_status = chdir(str[1][0]) == -1;
	if (str[0][1] && dir && access(str[0][1], F_OK) != -1)
		chdir(str[0][1]);
	else if (str[0][1] && access(str[0][1], F_OK) == -1)
		ft_perror(NDIR, str[0][1], 1);
	else if (str[0][1] && !S_ISDIR(path_stat.st_mode))
		ft_perror(NOT_DIR, str[0][1], 1);
	else if (str[0][1] && access(str[0][1], W_OK) == -1)
		ft_perror(NPERM, str[0][1], 1);
	if (str[0][1] && dir)
		closedir(dir);
}

/*
** Mimics cd command and updates OLDPWD and PWD
*/
int	ft_cd(t_prompt *p)
{
	char	**str[2];
	char	*tmp;

	g_status = 0;
	str[0] = ((t_mini *)p->cmds->content)->full_cmd;
	tmp = ft_getenv("HOME", p->env, 4);
	if (!tmp)
		tmp = ft_strdup("");
	str[1] = ft_extend_2d_arr(NULL, tmp);
	free(tmp);
	tmp = getcwd(NULL, 0);
	str[1] = ft_extend_2d_arr(str[1], tmp);
	free(tmp);
	exec_cd(str);
	if (!g_status)
		p->env = ft_setenv("OLDPWD", str[1][1], p->env, 6);
	tmp = getcwd(NULL, 0);
	if (!tmp)
		tmp = ft_strdup("");
	str[1] = ft_extend_2d_arr(str[1], tmp);
	free(tmp);
	p->env = ft_setenv("PWD", str[1][2], p->env, 3);
	ft_free_2d_array(&str[1]);
	return (g_status);
}

/*
** Mimics pwd command
*/
int	ft_pwd(void)
{
	char	*str;

	str = getcwd(NULL, 0);
	ft_putendl_fd(str, 1);
	free(str);
	return (0);
}

/*
** Mimics echo command
** flags_newline handles -n option
** flag i[1] checks if "-n" is an option or a string to print
*/
int	ft_echo(t_list *cmd)
{
	int		flag_newline;
	int		i[2];
	char	**av;
	t_mini	*node;

	i[0] = 0;
	i[1] = 0;
	flag_newline = 1;
	node = cmd->content;
	av = node->full_cmd;
	while (av && av[++i[0]])
	{
		if (!i[1] && check_echo_opt(av[i[0]]))
			flag_newline = 0;
		else
		{
			i[1] = 1;
			ft_putstr_fd(av[i[0]], 1);
			if (av[i[0] + 1])
				ft_putchar_fd(' ', 1);
		}
	}
	if (flag_newline)
		ft_putchar_fd('\n', 1);
	return (0);
}
