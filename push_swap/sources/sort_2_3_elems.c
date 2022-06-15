#include "../includes/push_swap.h"

void	sort_two_elems(t_list **a)
{
	sa(a, 1);
}

void	sort_three_elems(t_list **a)
{
	int		i;
	int		j;
	int		k;

	i = (*a)->number;
	j = (*a)->next->number;
	k = (*a)->next->next->number;
	if (i > j && i < k && j < k)
		sa(a, 1);
	else if (i > j && j > k)
	{
		ra(a, 1);
		sa(a, 1);
	}
	else if (i > j && i > k && j < k)
		ra(a, 1);
	else if (i < j && i < k && j > k)
	{
		sa(a, 1);
		ra(a, 1);
	}
	else if (i > k && i < j)
		rra(a, 1);
}
