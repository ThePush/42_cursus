#include "../includes/push_swap.h"

void	execute(t_list **a)
{
	t_list	*b;

	if (ft_lstsize(*a) > 45)
		radix_sort(a, &b, ft_lstsize(*a));
	else if (ft_lstsize(*a) > 3)
		selection_sort(a, &b);
	else if (ft_lstsize(*a) == 3)
		sort_three_elems(a);
	else if (ft_lstsize(*a) == 2)
		sort_two_elems(a);
	ft_lstclear(*a);
}
