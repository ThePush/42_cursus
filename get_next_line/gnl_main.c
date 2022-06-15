
#include <stdio.h>
#include "get_next_line_bonus.h"

int	main (int ac, char **av)
{
	int		fd0;
	int		fd1;
	int		fd2;
	int		fd42;
	char	*line;
	char	*line1;
	char    *line2;
	char	*line42;
	(void)ac;

	fd0 = open(av[1], O_RDONLY);
	fd1 = open(av[2], O_RDONLY);
	fd2 = open(av[3], O_RDONLY);

	/* STANDARD INPUT*/

	if (!av[1])
	{
		close(fd0);
		fd0 = 0;
	}

	/* TEST WITH MULTIPLE FD */

	printf("\nfd0 = %d\n", fd0);
	while ((line = get_next_line(fd0)))
	{
		printf("%s", line);
		free(line);
	}
	printf("\nfd1 = %d\n", fd1);
	if (fd1)
	{
		while ((line1 = get_next_line(fd1)))
		{
			printf("%s", line1);
			free(line1);
		}
	}

	/* DISPLAY ONLY ONE LINE */

	printf("\nfd2 = %d\n", fd2);
	line2 = get_next_line(fd2);
	printf("%s", line2);
	free(line2);
	


	/* TEST WITH INVALID FD */

	fd42 = 42;
	printf("\nfd42 = %d\n", fd42);
	printf("%s",(line42 = get_next_line(fd42)));
	printf("\n");
	free(line42);

	close(fd0);
	close(fd1);
	close(fd2);
	close(fd42);
}
