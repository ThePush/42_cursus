#include "../includes/push_swap.h"

static void	uplift_min(t_list **a, size_t min_index)
{
	size_t	list_length;

	list_length = ft_lstsize(*a);
	if (min_index == 1)
		sa(a, 1);
	else if (min_index > 1)
	{
		if (min_index <= list_length / 2)
		{
			while (min_index--)
				ra(a, 1);
		}
		else
		{
			while (list_length - min_index)
			{
				rra(a, 1);
				min_index++;
			}
		}
	}
}

void	selection_sort(t_list **a, t_list **b)
{
	size_t	min_index;
	size_t	diff;
	size_t	curr_length;
	size_t	total_length;

	curr_length = ft_lstsize(*a);
	total_length = ft_lstsize(*a);
	while (curr_length)
	{
		min_index = get_min_index(*a);
		uplift_min(a, min_index);
		if (is_stack_sorted(a))
			break ;
		pb(a, b);
		curr_length--;
	}
	diff = total_length - curr_length;
	while (diff)
	{
		pa(a, b);
		diff--;
	}
}
