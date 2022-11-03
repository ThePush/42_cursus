#include <unistd.h>

static void	inter(char *s1, char *s2)
{
	int	tab[1000] = {0};
	int	i = 0;

	while (s2[i])
	{
		if (tab[(int)s2[i]] == 0)
			(tab[(int)s2[i]] = 1);
		i++;
	}
	i = 0;
	while (s1[i])
	{
		if (tab[(int)s1[i]] == 1)
		{
			(tab[(int)s1[i]] = 0);
			write(1, &s1[i], 1);
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 3)
		inter(av[1], av[2]);
	write(1, "\n", 1);
	return (0);
}
