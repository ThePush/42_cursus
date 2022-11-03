#include "../includes/push_swap.h"

int	main(int ac, char **av)
{
	t_list	*a;

	a = NULL;
	if (ac > 1)
	{
		check_list(ac, av);
		init_stack(ac, av, &a);
		execute(&a);
	}
	return (EXIT_SUCCESS);
}
