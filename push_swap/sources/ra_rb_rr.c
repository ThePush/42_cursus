#include "../includes/push_swap.h"

void	ra(t_list **a, int write_op)
{
	t_list	*tmp;

	if (!*a)
		return ;
	tmp = *a;
	*a = (*a)->next;
	tmp->next = NULL;
	ft_lstadd_back(a, tmp);
	if (write_op)
		write(1, "ra\n", 3);
}

void	rb(t_list **b, int write_op)
{
	t_list	*tmp;

	if (!*b)
		return ;
	tmp = *b;
	*b = (*b)->next;
	tmp->next = NULL;
	ft_lstadd_back(b, tmp);
	if (write_op)
		write(1, "rb\n", 3);
}

void	rr(t_list **a, t_list **b)
{
	ra(a, 0);
	rb(b, 0);
	write(1, "rr\n", 3);
}
