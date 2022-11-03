#include "../includes/push_swap.h"

void	sa(t_list **a, int write_op)
{
	int	tmp;

	if (!*a || !(*a)->next)
		return ;
	tmp = (*a)->number;
	(*a)->number = (*a)->next->number;
	(*a)->next->number = tmp;
	if (write_op)
		write(1, "sa\n", 3);
}

void	sb(t_list **b, int write_op)
{
	int	tmp;

	if (!*b || !(*b)->next)
		return ;
	tmp = (*b)->number;
	(*b)->number = (*b)->next->number;
	(*b)->next->number = tmp;
	if (write_op)
		write(1, "sb\n", 3);
}

void	ss(t_list **a, t_list **b)
{
	sa(a, 0);
	sb(b, 0);
	write(1, "ss\n", 3);
}
