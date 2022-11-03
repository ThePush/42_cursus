/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prompt_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:54:59 by jsemel            #+#    #+#             */
/*   Updated: 2022/04/27 23:13:46 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

static char	*get_home(t_prompt prompt)
{
	char	*tmp;
	char	*pwd;
	char	*home;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("∅ ");
	home = ft_getenv("HOME", prompt.env, 4);
	if (home && home[0] && ft_strnstr(pwd, home, ft_strlen(pwd)))
	{
		tmp = pwd;
		pwd = ft_strjoin("~", &pwd[ft_strlen(home)]);
		free(tmp);
	}
	free(home);
	home = ft_strjoin(BLUE, pwd);
	free(pwd);
	pwd = ft_strjoin(home, DEFAULT);
	free(home);
	return (pwd);
}

/*
** fd = fd[READ_END]
*/
static void	update_output(char ***user, int fd)
{
	char	**arr_tmp;
	char	*temp;
	char	*line;

	arr_tmp = NULL;
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		temp = ft_strtrim(line, "\n");
		free(line);
		arr_tmp = ft_extend_2d_arr(arr_tmp, temp);
		free(temp);
	}
	ft_free_2d_array(user);
	*user = arr_tmp;
}

void	exec_whoami(char ***user, char *path_cmd, char *cmd, char **env)
{
	pid_t	pid;
	int		fd[2];
	char	**td_array;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[READ_END]);
		td_array = ft_split(cmd, ' ');
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		if (!access(path_cmd, F_OK))
			execve(path_cmd, td_array, env);
		exit (1);
	}
	close(fd[WRITE_END]);
	waitpid(pid, NULL, 0);
	update_output(user, fd[READ_END]);
	close(fd[READ_END]);
}

static char	*get_user(t_prompt prompt)
{
	char	**user;
	char	*temp;
	char	*temp2;

	user = NULL;
	temp2 = NULL;
	exec_whoami(&user, "/usr/bin/whoami", "whoami", prompt.env);
	if (!user)
		user = ft_extend_2d_arr(user, "(guest");
	temp2 = ft_strjoin(NULL, CYAN);
	temp = ft_strjoin(temp2, *user);
	free(temp2);
	ft_free_2d_array(&user);
	return (temp);
}

char	*get_prompt(t_prompt prompt)
{
	char	*ret;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	ret = get_user(prompt);
	tmp2 = ft_strjoin("┌──(", ret);
	free(ret);
	ret = ft_strjoin(CYAN, tmp2);
	free(tmp2);
	tmp = ft_strjoin(ret, "@minishell)-[");
	free(ret);
	tmp3 = get_home(prompt);
	ret = ft_strjoin(tmp, tmp3);
	free(tmp3);
	free(tmp);
	tmp2 = ft_strjoin(CYAN, "]\n└─$ ");
	tmp = ft_strjoin(ret, tmp2);
	free(ret);
	free(tmp2);
	ret = ft_strjoin(tmp, DEFAULT);
	free(tmp);
	return (ret);
}
