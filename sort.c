/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 21:46:21 by jesuserr          #+#    #+#             */
/*   Updated: 2023/05/10 13:07:36 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_stack(t_stack *lst_a, t_stack *lst_b)
{
	if (lst_a->size == 2)
		swap(lst_a);
	if (lst_a->size == 3)
		sort_triplet(lst_a);
	if (lst_a->size >= 4 && lst_a->size <= 25)
		sort_under_25(lst_a, lst_b);
	if (lst_a->size > 25)
		sort_over_25(lst_a, lst_b);
}

void	sort_triplet(t_stack *lst)
{
	int	value_1;
	int	value_2;
	int	value_3;

	value_1 = lst->head->parse;
	value_2 = lst->head->next->parse;
	value_3 = lst->head->next->next->parse;
	if ((value_1 < value_2) && (value_2 > value_3) && (value_1 < value_3))
	{
		swap(lst);
		rotate(lst);
	}
	else if ((value_1 > value_2) && (value_2 < value_3) && (value_1 < value_3))
		swap(lst);
	else if ((value_1 < value_2) && (value_2 > value_3) && (value_1 > value_3))
		reverse_rotate(lst);
	else if ((value_1 > value_2) && (value_2 < value_3) && (value_1 > value_3))
		rotate(lst);
	else if ((value_1 > value_2) && (value_2 > value_3) && (value_1 > value_3))
	{
		swap(lst);
		reverse_rotate(lst);
	}	
}

void	sort_under_25(t_stack *lst_a, t_stack *lst_b)
{
	size_t	position;
	int		direction;

	while (lst_a->size > 3 && !list_is_sorted(lst_a))
	{	
		position = smallest_nbr_position(lst_a);
		direction = reverse_or_not_reverse(lst_a, &position);
		while (position > 0)
		{
			if (direction == ROTATE_UP)
				rotate(lst_a);
			else
				reverse_rotate(lst_a);
			position--;
		}
		if (!list_is_sorted(lst_a))
			push(lst_a, lst_b);
	}
	sort_triplet(lst_a);
	while (lst_b->size)
		push(lst_b, lst_a);
}

void	sort_over_25(t_stack *lst_a, t_stack *lst_b)
{
	size_t	chunk_size;

	chunk_size = (lst_a->size * 3 / 40) + (22.5);
	move_to_b(lst_a, lst_b, lst_a->size, chunk_size);
	sort_triplet(lst_a);
	move_back_to_stack_a(lst_b, lst_a);
}
