/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:21:59 by jsemel            #+#    #+#             */
/*   Updated: 2022/04/10 10:54:53 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Loop on path splitted on " : " to find command's path
*/
static char	*get_cmd_path(char **env_path, char *cmd, char *full_path)
{
	char	*tmp;
	int		i;

	i = -1;
	full_path = NULL;
	while (env_path && env_path[++i])
	{
		free(full_path);
		tmp = ft_strjoin(env_path[i], "/");
		if (!tmp)
			return (NULL);
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			break ;
	}
	if (!env_path || !env_path[i])
	{
		free(full_path);
		return (NULL);
	}
	return (full_path);
}

static DIR	*parse_cmd(t_prompt *prompt, t_list *cmd, char ***s, char *path)
{
	t_mini	*node;
	DIR		*dir;

	dir = NULL;
	node = cmd->content;
	if (node && node->full_cmd)
		dir = opendir(*node->full_cmd);
	if (node && node->full_cmd && ft_strchr(*node->full_cmd, '/') && !dir)
	{
		*s = ft_split(*node->full_cmd, '/');
		node->full_path = ft_strdup(*node->full_cmd);
		free(node->full_cmd[0]);
		node->full_cmd[0] = ft_strdup(s[0][ft_2d_arr_len(*s) - 1]);
	}
	else if (!is_builtin(node) && node && node->full_cmd && !dir)
	{
		path = ft_getenv("PATH", prompt->env, 4);
		*s = ft_split(path, ':');
		free(path);
		node->full_path = get_cmd_path(*s, *node->full_cmd, node->full_path);
		if (!node->full_path || !node->full_cmd[0] || !node->full_cmd[0][0])
			ft_perror(NCMD, *node->full_cmd, 127);
	}
	return (dir);
}

/*
** Self explanatory
** 126 - Command invoked cannot execute
** 127 - “command not found”
*/
static void	handle_cmd(t_prompt *p, t_list *cmd, char **s, char *path)
{
	t_mini	*node;
	DIR		*dir;

	node = cmd->content;
	dir = parse_cmd(p, cmd, &s, path);
	if (!is_builtin(node) && node && node->full_cmd && dir)
		ft_perror(IS_DIR, *node->full_cmd, 126);
	else if (!is_builtin(node) && node && node->full_path && \
		access(node->full_path, F_OK) == -1)
		ft_perror(NDIR, node->full_path, 127);
	else if (!is_builtin(node) && node && node->full_path && \
		access(node->full_path, X_OK) == -1)
		ft_perror(NPERM, node->full_path, 126);
	if (dir)
		closedir(dir);
	ft_free_2d_array(&s);
}

void	*exec_cmd(t_prompt *prompt, t_list *cmd)
{
	int		fd[2];

	handle_cmd(prompt, cmd, NULL, NULL);
	if (pipe(fd) == -1)
		return (ft_perror(PIPERR, NULL, 1));
	if (!fork_handler(prompt, cmd, fd))
		return (NULL);
	close(fd[WRITE_END]);
	if (cmd->next && !((t_mini *)cmd->next->content)->infile)
		((t_mini *)cmd->next->content)->infile = fd[READ_END];
	else
		close(fd[READ_END]);
	if (((t_mini *)cmd->content)->infile > 2)
		close(((t_mini *)cmd->content)->infile);
	if (((t_mini *)cmd->content)->outfile > 2)
		close(((t_mini *)cmd->content)->outfile);
	return (NULL);
}
