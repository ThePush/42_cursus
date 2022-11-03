#include "../includes/push_swap.h"

int	get_min_index(t_list *list)
{
	int			min_number;
	size_t		min_index;
	size_t		i;
	t_list		*tmp;

	min_number = list->number;
	min_index = 0;
	i = 1;
	tmp = list->next;
	while (tmp)
	{
		if (min_number > tmp->number)
		{
			min_number = tmp->number;
			min_index = i;
		}
		tmp = tmp->next;
		i++;
	}
	return (min_index);
}

static int	get_max_index(t_list **list)
{
	t_list	*tmp;
	int		max_index;

	tmp = *list;
	max_index = tmp->index;
	while (tmp)
	{
		if (tmp->index > max_index)
			max_index = tmp->index;
		tmp = tmp->next;
	}
	return (max_index);
}

int	get_shift_pos(t_list **list)
{
	int		max_index;
	int		shift_pos;

	max_index = get_max_index(list);
	shift_pos = 0;
	while (max_index >> shift_pos)
		shift_pos++;
	return (shift_pos);
}
