/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 21:47:29 by jesuserr          #+#    #+#             */
/*   Updated: 2023/05/07 13:45:56 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t	rotates_to_top(t_stack *lst, size_t min, size_t max)
{
	t_node	*tmp;
	size_t	position;	

	tmp = lst->head;
	position = 1;
	while (tmp)
	{
		if (tmp->parse >= min && tmp->parse <= max)
			return (position - 1);
		tmp = tmp->next;
		position++;
	}
	return (-1);
}

void	move_to_b(t_stack *lst_a, t_stack *lst_b, size_t a_sz, size_t chunk_sz)
{
	size_t	chunk_max;
	size_t	i;

	chunk_max = chunk_sz;
	while (lst_a->size > 3)
	{
		i = chunk_sz;
		while (i--)
		{
			while (rotates_to_top(lst_a, chunk_max - chunk_sz, chunk_max) > 0)
				rotate(lst_a);
			if (lst_a->head->parse < a_sz - 2)
				push (lst_a, lst_b);
			else
				rotate(lst_a);
			if (lst_b->head->parse > ((chunk_max + chunk_max - chunk_sz) / 2)
				&& (lst_a->size && lst_a->head->parse > chunk_max))
				rotate_both(lst_a, lst_b);
			else if (lst_b->head->parse > ((2 * chunk_max - chunk_sz) / 2))
				rotate (lst_b);
		}
		if (chunk_sz > lst_a->size)
			chunk_sz = lst_a->size;
		chunk_max = chunk_max + chunk_sz;
	}
}

void	move_back_to_stack_a(t_stack *lst_b, t_stack *lst_a)
{
	size_t	position;
	int		direction;
	size_t	parsed_value;
	int		flag;

	while (lst_b->size)
	{	
		position = biggest_nbr_position(lst_b, &parsed_value);
		direction = reverse_or_not_reverse(lst_b, &position);
		flag = 0;
		while (position--)
		{
			rotate_or_reverse(direction, lst_b);
			if (lst_b->head->parse == parsed_value - 1)
			{
				push(lst_b, lst_a);
				position = biggest_nbr_position(lst_b, &parsed_value);
				direction = reverse_or_not_reverse(lst_b, &position);
				flag = 1;
			}			
		}
		push(lst_b, lst_a);
		if (flag == 1)
			swap(lst_a);
	}
}

void	rotate_or_reverse(int direction, t_stack *lst_b)
{
	if (direction == ROTATE_UP)
		rotate(lst_b);
	else
		reverse_rotate(lst_b);
}

size_t	biggest_nbr_position(t_stack *lst, size_t *value)
{
	t_node	*tmp;
	size_t	max_value;
	size_t	position;
	size_t	i;

	tmp = lst->head;
	max_value = lst->head->parse;
	i = 1;
	position = 1;
	while (tmp)
	{
		if (tmp->parse > max_value)
		{
			max_value = tmp->parse;
			position = i;
		}
		tmp = tmp->next;
		i++;
	}
	*value = max_value;
	return (position);
}
