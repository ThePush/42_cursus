/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:17:08 by jsemel            #+#    #+#             */
/*   Updated: 2022/04/22 11:41:43 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

/*
** Execute builtin
*/
void	child_builtin(t_prompt *prompt, t_mini *n, int cmd_length, t_list *cmd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!is_builtin(n) && n->full_cmd)
		execve(n->full_path, n->full_cmd, prompt->env);
	else if (n->full_cmd && !ft_strncmp(*n->full_cmd, "pwd", cmd_length) \
		&& cmd_length == 3)
		g_status = ft_pwd();
	else if (is_builtin(n) && n->full_cmd && \
		!ft_strncmp(*n->full_cmd, "echo", cmd_length) && cmd_length == 4)
		g_status = ft_echo(cmd);
	else if (is_builtin(n) && n->full_cmd && \
		!ft_strncmp(*n->full_cmd, "env", cmd_length) && cmd_length == 3)
	{
		ft_put_2darr_fd(prompt->env, 1, 1);
		g_status = 0;
	}
}

/*
** Initialises fd's in nodes and then connects them
*/
static void	*child_redir(t_list *cmd, int fd[2])
{
	t_mini	*node;

	node = cmd->content;
	if (node->infile != STDIN_FILENO)
	{
		if (dup2(node->infile, STDIN_FILENO) == -1)
			return (ft_perror(DUPERR, NULL, 1));
		close(node->infile);
	}
	if (node->outfile != STDOUT_FILENO)
	{
		if (dup2(node->outfile, STDOUT_FILENO) == -1)
			return (ft_perror(DUPERR, NULL, 1));
		close(node->outfile);
	}
	else if (cmd->next && dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
		return (ft_perror(DUPERR, NULL, 1));
	close(fd[WRITE_END]);
	return ("");
}

static void	*child_process(t_prompt *prompt, t_list *cmd, int fd[2])
{
	t_mini	*node_content;
	int		cmd_length;

	node_content = cmd->content;
	cmd_length = 0;
	if (node_content->full_cmd)
		cmd_length = ft_strlen(*node_content->full_cmd);
	child_redir(cmd, fd);
	close(fd[READ_END]);
	child_builtin(prompt, node_content, cmd_length, cmd);
	ft_lstclear(&prompt->cmds, free_content);
	ft_free_2d_array(&prompt->env);
	exit(g_status);
}

/*
** Just fork and go in child_process
*/
static void	exec_fork(t_prompt *prompt, t_list *cmd, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		ft_perror(FORKERR, NULL, 1);
	}
	else if (pid == 0)
		child_process(prompt, cmd, fd);
}

/*
** if open() failed at fd_handler(), function returns NULL
** exit_code 126 = command cannot execute
** exit_code 127 = command not found
*/
void	*fork_handler(t_prompt *prompt, t_list *cmd, int fd[2])
{
	t_mini	*n;
	DIR		*dir;

	n = cmd->content;
	dir = NULL;
	if (n->full_cmd)
		dir = opendir(*n->full_cmd);
	if (n->infile == -1 || n->outfile == -1)
		return (NULL);
	if ((n->full_path && access(n->full_path, X_OK) == 0) || is_builtin(n))
		exec_fork(prompt, cmd, fd);
	else if (!is_builtin(n) && ((n->full_path && \
		!access(n->full_path, F_OK)) || dir))
		g_status = 126;
	else if (!is_builtin(n) && n->full_cmd)
		g_status = 127;
	if (dir)
		closedir(dir);
	return ("");
}
