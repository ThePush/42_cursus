/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:10:29 by jsemel            #+#    #+#             */
/*   Updated: 2022/04/08 12:40:04 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

int	builtin(t_prompt *prompt, t_list *cmd, int *is_exit, int n)
{
	char	**a;

	while (cmd)
	{
		a = ((t_mini *)cmd->content)->full_cmd;
		n = 0;
		if (a)
			n = ft_strlen(*a);
		if (a && !ft_strncmp(*a, "exit", n) && n == 4)
			g_status = ft_exit(cmd, is_exit);
		else if (!cmd->next && a && !ft_strncmp(*a, "cd", n) && n == 2)
			g_status = ft_cd(prompt);
		else if (!cmd->next && a && !ft_strncmp(*a, "export", n) && n == 6)
			g_status = ft_export(prompt);
		else if (!cmd->next && a && !ft_strncmp(*a, "unset", n) && n == 5)
			g_status = ft_unset(prompt);
		else
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			exec_cmd(prompt, cmd);
		}
		cmd = cmd->next;
	}
	return (g_status);
}

/*
** Checks if the command is a builtin
*/
bool	is_builtin(t_mini *n)
{
	int		len;

	if (!n->full_cmd)
		return (false);
	if ((n->full_cmd && ft_strchr(*n->full_cmd, '/')) || (n->full_path && \
		ft_strchr(n->full_path, '/')))
		return (false);
	len = ft_strlen(*n->full_cmd);
	if (!ft_strncmp(*n->full_cmd, "pwd", len) && len == 3)
		return (true);
	if (!ft_strncmp(*n->full_cmd, "env", len) && len == 3)
		return (true);
	if (!ft_strncmp(*n->full_cmd, "cd", len) && len == 2)
		return (true);
	if (!ft_strncmp(*n->full_cmd, "export", len) && len == 6)
		return (true);
	if (!ft_strncmp(*n->full_cmd, "unset", len) && len == 5)
		return (true);
	if (!ft_strncmp(*n->full_cmd, "echo", len) && len == 4)
		return (true);
	if (!ft_strncmp(*n->full_cmd, "exit", len) && len == 4)
		return (true);
	return (false);
}
