/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:04:07 by jsemel            #+#    #+#             */
/*   Updated: 2022/04/26 14:38:59 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_mini	*mini_init(void)
{
	t_mini	*mini;

	mini = malloc(sizeof(t_mini));
	if (!mini)
		return (NULL);
	mini->full_cmd = NULL;
	mini->full_path = NULL;
	mini->infile = STDIN_FILENO;
	mini->outfile = STDOUT_FILENO;
	return (mini);
}

/*
** Handles [>>>] and [<<<]
*/
static bool	check_arrows(char ***a, int *i)
{
	if (a[0][*i][0] == '>' && a[0][*i + 1]
		&& a[0][*i + 1][0] == '>' && a[0][*i + 2] && a[0][*i + 2][0] == '>')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `>'", 2);
		*i = -2;
		return (false);
	}
	if (a[0][*i][0] == '<' && a[0][*i + 1]
		&& a[0][*i + 1][0] == '<' && a[0][*i + 2] && a[0][*i + 2][0] == '<')
	{
		ft_putendl_fd("minishell: `<<<' not recognized", 2);
		*i = -2;
		return (false);
	}
	return (true);
}

/*
** If a redirection symbol is found in the input, nodes are updated accordingly,
** else the command array is extended
*/
static t_mini	*parse_redir(t_mini *node, char **a[2], int *i, t_prompt *p)
{
	if (a[0][*i])
	{
		if (!(check_arrows(a, i)))
			return (node);
		if (a[0][*i][0] == '>' && a[0][*i + 1] && a[0][*i + 1][0] == '>')
			node = redir_append(node, a[1], i);
		else if (a[0][*i][0] == '>')
			node = redir_truncate(node, a[1], i);
		else if (a[0][*i][0] == '<' && a[0][*i + 1] && \
			a[0][*i + 1][0] == '<')
			node = redir_heredoc(node, a[1], i, p);
		else if (a[0][*i][0] == '<')
			node = redir_input(node, a[1], i);
		else if (a[0][*i][0] != '|')
			node->full_cmd = ft_extend_2d_arr(node->full_cmd, a[1][*i]);
		else
		{
			ft_perror(PIPENDERR, NULL, 2);
			*i = -2;
		}
		return (node);
	}
	ft_perror(PIPENDERR, NULL, 2);
	*i = -2;
	return (node);
}

/*
** Free memory
*/
static t_list	*clear_all(t_list *cmds, char **args, char **temp)
{
	ft_lstclear(&cmds, free_content);
	ft_free_2d_array(&temp);
	ft_free_2d_array(&args);
	return (NULL);
}

/*
** 1: Strim the quotes off the input
** 2: Create a linked list and fill it with t_mini structures
*/
t_list	*create_list(char **args, int i, t_prompt *p)
{
	t_list	*cmds[2];
	char	**temp[2];

	cmds[0] = NULL;
	temp[1] = quotes_trim(args);
	while (args[++i])
	{
		cmds[1] = ft_lstlast(cmds[0]);
		if (i == 0 || (args[i][0] == '|' && args[i + 1] && args[i + 1][0]))
		{
			i += args[i][0] == '|';
			ft_lstadd_back(&cmds[0], ft_lstnew(mini_init()));
			cmds[1] = ft_lstlast(cmds[0]);
		}
		temp[0] = args;
		cmds[1]->content = parse_redir(cmds[1]->content, temp, &i, p);
		if (i < 0)
			return (clear_all(cmds[0], args, temp[1]));
		if (!args[i])
			break ;
	}
	ft_free_2d_array(&temp[1]);
	ft_free_2d_array(&args);
	return (cmds[0]);
}
