#include "../includes/push_swap.h"

void	radix_sort(t_list **a, t_list **b, size_t list_length)
{
	t_list		*tmp;
	int			i;
	size_t		j;
	int			max_shift_pos;

	tmp = *a;
	i = -1;
	max_shift_pos = get_shift_pos(a);
	while (++i < max_shift_pos)
	{
		j = -1;
		while (++j < list_length)
		{
			tmp = *a;
			if ((tmp->index >> i) & 1)
				ra(a, 1);
			else
				pb(a, b);
		}
		while (*b)
			pa(a, b);
	}
}
