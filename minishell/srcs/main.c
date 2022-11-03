/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:07:58 by jsemel            #+#    #+#             */
/*   Updated: 2022/04/22 10:48:21 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

/*
** fork() to get pid
*/
static void	ft_getpid(t_prompt *prompt)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_perror(FORKERR, NULL, 1);
		ft_free_2d_array(&prompt->env);
		exit(1);
	}
	if (pid == 0)
	{
		ft_free_2d_array(&prompt->env);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	prompt->pid = pid - 1;
}

static t_prompt	init_prompt(char **av, char **env)
{
	t_prompt	prompt;
	char		*val;

	val = NULL;
	prompt.cmds = NULL;
	prompt.env = ft_dup_2d_array(env);
	g_status = 0;
	ft_getpid(&prompt);
	prompt = init_env(prompt, val, av);
	return (prompt);
}

int	main(int ac, char **av, char **envp)
{
	char		*str;
	char		*input;
	t_prompt	prompt;

	prompt = init_prompt(av, envp);
	while (av && ac)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTERM, signal_handler);
		str = get_prompt(prompt);
		if (str)
			input = readline(str);
		else
			input = readline("guest@minishell $ ");
		free(str);
		if (!exec_prog(input, &prompt))
			break ;
	}
	ft_free_2d_array(&prompt.env);
	close(0);
	close(1);
	close(2);
	exit(g_status);
}
