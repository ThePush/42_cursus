#include "../includes/push_swap.h"

static bool	no_duplicates_in_stack(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = i + 1;
		while (av[j])
		{
			if (av[i] == av[j])
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

static long	ft_atoi_ps(char *str)
{
	int		i;
	long	nb;
	int		neg;

	i = 0;
	nb = 0;
	neg = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -neg;
		i++;
	}
	if (str[i] < '0' || str[i] > '9')
		return (LONG_MAX);
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i] - 48;
		i++;
	}
	if (str[i])
		return (LONG_MAX);
	return (nb * neg);
}

static bool	valid_numbers(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_strlen(av[i]) > 11 || ft_atoi_ps(av[i]) > INT_MAX
			|| ft_atoi_ps(av[i]) < INT_MIN)
			return (false);
		i++;
	}
	return (true);
}

void	check_list(int ac, char **av)
{
	if (!(no_duplicates_in_stack(av)))
	{
		ft_perror();
		exit(EXIT_FAILURE);
	}
	if (!(valid_numbers(ac, av)))
	{
		ft_perror();
		exit(EXIT_FAILURE);
	}
}
