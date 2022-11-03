/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 10:22:31 by jsemel            #+#    #+#             */
/*   Updated: 2022/04/22 17:30:09 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

/*
** Free array and close fd's
*/
void	free_content(void *content)
{
	t_mini	*node;

	node = content;
	ft_free_2d_array(&node->full_cmd);
	free(node->full_path);
	if (node->infile != STDIN_FILENO && node->infile != -1)
		close(node->infile);
	if (node->outfile != STDOUT_FILENO && node->outfile != -1)
		close(node->outfile);
	free(node);
}
