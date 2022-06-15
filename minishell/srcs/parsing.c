/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:48:21 by jsemel            #+#    #+#             */
/*   Updated: 2022/04/20 23:36:37 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

/*
** Expand variables and split the input again with symbols "<|>" as delimiters,
** turning the input into a fully splitted 2D array
*/
static char	**parse_input(char **args, t_prompt *prompt)
{
	char	**symsplit;
	int		i[3];
	int		quotes[2];

	i[0] = -1;
	while (args && args[++i[0]])
	{
		i[1] = -1;
		i[2] = -1;
		args[i[0]] = expand_vars(args[i[0]], -1, quotes, prompt);
		i[1] = ft_strchars_i(args[i[0]], "~");
		i[2] = ft_strlen(args[i[0]]);
		if (((i[1] == 0 && ((i[2] == 1)
						|| ((i[2] > 1 && args[i[0]][1] == '/'))))))
			args[i[0]] = expand_path(args[i[0]], -1, quotes, \
				ft_getenv("HOME", prompt->env, 4));
		symsplit = ft_symsplit(args[i[0]], "<|>");
		ft_arr_replace_in(&args, symsplit, i[0]);
		i[0] += ft_2d_arr_len(symsplit) - 1;
		ft_free_2d_array(&symsplit);
	}
	return (args);
}

/*
** handle exit code from the waitpid in parse_args
*/
int	g_status_handler(long status)
{
	if (status > 255)
		status /= 255;
	if (status == 256)
		status = 255;
	return (status);
}

/*
** 1: Create a linked list with our splitted input
*/
static void	*parse_args(char **args, t_prompt *p)
{
	int	is_exit;
	int	i;

	is_exit = 0;
	p->cmds = create_list(parse_input(args, p), -1, p);
	if (!p->cmds)
		return (p);
	i = ft_lstsize(p->cmds);
	g_status = builtin(p, p->cmds, &is_exit, 0);
	while (i-- > 0)
		waitpid(-1, &g_status, 0);
	if (!is_exit && g_status == 13)
		g_status = 0;
	g_status = g_status_handler(g_status);
	if (args && is_exit)
	{
		ft_free_2d_array(&p->env);
		ft_lstclear(&p->cmds, free_content);
		return (NULL);
	}
	return (p);
}

/*
** 1: Split the input with spaces as delimiter with ft_argsplit
** 2: Update the prompt, commands and environment
 */
void	*exec_prog(char *input, t_prompt *p)
{
	char	**splitted_input;
	t_mini	*n;

	if (!input)
	{
		printf("exit\n");
		return (NULL);
	}
	if (input[0] != '\0')
		add_history(input);
	splitted_input = ft_input_split(input, " ");
	free(input);
	if (!splitted_input)
		ft_perror(QUOTE, NULL, 1);
	if (!splitted_input)
		return ("");
	p = parse_args(splitted_input, p);
	if (p && p->cmds)
		n = p->cmds->content;
	if (p && p->cmds && n && n->full_cmd && ft_lstsize(p->cmds) == 1)
		p->env = ft_setenv("_", n->full_cmd[ft_2d_arr_len(n->full_cmd) - 1], \
			p->env, 1);
	if (p && p->cmds)
		ft_lstclear(&p->cmds, free_content);
	return (p);
}
