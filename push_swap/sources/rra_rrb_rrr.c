#include "../includes/push_swap.h"

void	rra(t_list **a, int write_op)
{
	t_list	*penul;
	t_list	*last_elem;
	t_list	*list;

	if (!*a || !(*a)->next)
		return ;
	penul = *a;
	list = *a;
	while (penul->next->next)
		penul = penul->next;
	last_elem = penul->next;
	penul->next = NULL;
	last_elem->next = list;
	*a = last_elem;
	if (write_op)
		write(1, "rra\n", 4);
}

void	rrb(t_list **b, int write_op)
{
	t_list	*penul;
	t_list	*last_elem;
	t_list	*list;

	if (!*b || !(*b)->next)
		return ;
	penul = *b;
	list = *b;
	while (penul->next->next)
		penul = penul->next;
	last_elem = penul->next;
	penul->next = NULL;
	last_elem->next = list;
	*b = last_elem;
	if (write_op)
		write(1, "rrb\n", 4);
}

void	rrr(t_list **a, t_list **b)
{
	rra(a, 0);
	rrb(b, 0);
	write(1, "rrr\n", 4);
}
