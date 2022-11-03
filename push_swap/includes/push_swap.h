/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:11:54 by jsemel            #+#    #+#             */
/*   Updated: 2022/06/15 11:09:05 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

// push_swap operations
void	pa(t_list **a, t_list **b);
void	pb(t_list **a, t_list **b);

void	ra(t_list **a, int write_op);
void	rb(t_list **b, int write_op);
void	rr(t_list **a, t_list **b);

void	rra(t_list **a, int write_op);
void	rrb(t_list **b, int write_op);
void	rrr(t_list **a, t_list **b);

void	sa(t_list **a, int write_op);
void	sb(t_list **b, int write_op);
void	ss(t_list **a, t_list **b);

// Utils
int		get_min_index(t_list *list);
int		get_shift_pos(t_list **list);
bool	is_stack_sorted(t_list **list);
void	ft_perror(void);

// Sorting functions
void	sort_two_elems(t_list **a);
void	sort_three_elems(t_list **a);
void	selection_sort(t_list **a, t_list **b);
void	radix_sort(t_list **a, t_list **b, size_t list_length);

//checking
void	check_list(int ac, char **av);

// Execution
void	execute(t_list **a);

// Load stack a
t_list	**init_stack(int ac, char **av, t_list **a);

#endif
