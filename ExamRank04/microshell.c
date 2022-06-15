#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define READ_END 0
#define WRITE_END 1

int	ft_perror(char *str, char *arg)
{
	while (*str)
		write(2, str++, 1);
	if (arg)
		while (*arg)
			write(2, arg++, 1);
	write(2, "\n", 1);
	return (1);
}

void	fatal(void)
{
	ft_perror("error: fatal", NULL);
	exit(1);
}

int	ft_execute(char **av, int i, int tmp_fd, char **env)
{
	av[i] = NULL;
	close(tmp_fd);
	execve(av[0], av, env);
	return(ft_perror("error: cannot execute: ", av[0]));
}

int	main(int ac, char **av, char **env)
{
	int	i = 0, fd[2], tmp_fd;
	pid_t	pid = 0;

	(void)ac;
	if ((tmp_fd = dup(STDIN_FILENO)) == -1)
		fatal();
	while (av[i] && av[i + 1])
	{
		av = &av[i + 1];
		i = 0;
		while (av[i] && (strcmp(av[i], ";") && strcmp(av[i], "|")))
			i++;
		if (!strcmp(av[0], "cd"))
		{
			if (i != 2)
				ft_perror("error: cd: bad arguments", NULL);
			else if (chdir(av[1]) != 0)
				ft_perror("error: cd: cannot change directory to ", av[1]);
		}
		else if (i != 0 && (av[i] == NULL || strcmp(av[i], ";") == 0))
		{
			if((pid = fork()) == -1)
				fatal();
			if (pid == 0)
			{
				if (dup2(tmp_fd, STDIN_FILENO) == -1)
					fatal();
				if (ft_execute(av, i, tmp_fd, env))
					return (1);
			}
			else
			{
				close(tmp_fd);
				waitpid(-1, NULL, WUNTRACED);
				if ((tmp_fd = dup(STDIN_FILENO)) == -1)
					fatal();
			}
		}
		else if (i != 0 && strcmp(av[i], "|") == 0)
		{
			if(pipe(fd) == -1 || (pid = fork()) == -1)
				fatal();
			if (pid == 0)
			{
				if (dup2(tmp_fd, STDIN_FILENO) == -1)
					fatal();
				if (dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
					fatal();
				close(fd[WRITE_END]);
				close(fd[READ_END]);
				if (ft_execute(av, i, tmp_fd, env))
					return (1);
			}
			else
			{
				close(tmp_fd);
				close(fd[WRITE_END]);
				waitpid(-1, NULL, WUNTRACED);
				if ((tmp_fd = dup(fd[READ_END])) == -1)
					fatal();
				close(fd[READ_END]);
			}
		}
	}
	close(tmp_fd);
	return (0);
}
