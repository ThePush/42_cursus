#include "../includes/push_swap.h"

bool	is_stack_sorted(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp && tmp->next)
	{
		if (tmp->number > (tmp->next)->number)
			return (false);
		tmp = tmp->next;
	}
	return (true);
}
