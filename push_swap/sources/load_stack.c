#include "../includes/push_swap.h"

static void	load_index_util(t_list *lst, int i)
{
	t_list	*minimum;
	t_list	*tmp;

	minimum = lst;
	tmp = lst;
	while (minimum->index > -1)
		minimum = minimum->next;
	while (tmp)
	{
		if (tmp->index == -1 && minimum->number > tmp->number)
			minimum = tmp;
		tmp = tmp->next;
	}
	minimum->index = i;
}

static void	load_index(t_list **a)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = *a;
	while (i < ft_lstsize(tmp))
	{
		load_index_util(tmp, i);
		i++;
	}
}

t_list	**init_stack(int ac, char **av, t_list **a)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		ft_lstadd_back(a, ft_lstnew(ft_atoi(av[i])));
		i++;
	}
	if (!a)
	{
		ft_perror();
		ft_lstclear(*a);
		exit(EXIT_FAILURE);
	}
	load_index(a);
	if (is_stack_sorted(a))
	{
		ft_lstclear(*a);
		exit(EXIT_SUCCESS);
	}
	return (a);
}
