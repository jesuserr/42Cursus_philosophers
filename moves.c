/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:14:38 by jesuserr          #+#    #+#             */
/*   Updated: 2023/05/05 23:39:05 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_stack *lst)
{
	int		temp;
	size_t	temp2;

	if (lst->size > 1)
	{
		temp = lst->head->value;
		temp2 = lst->head->parse;
		lst->head->value = lst->head->next->value;
		lst->head->parse = lst->head->next->parse;
		lst->head->next->value = temp;
		lst->head->next->parse = temp2;
		if (lst->name == 'a')
			write (1, "sa\n", 3);
		else
			write (1, "sb\n", 3);
	}
}

void	push(t_stack *lst_a, t_stack *lst_b)
{
	t_node	*temp;

	if (lst_a->size == 0)
	{
		write (1, RED"Empty Stack - Nothing to push\n"WHITE, 44);
		return ;
	}	
	temp = lst_a->head->next;
	ft_add_node_front(lst_b, lst_a->head);
	lst_a->size--;
	if (lst_a->size == 0)
		lst_a->tail = NULL;
	lst_a->head = temp;
	if (lst_a->name == 'a')
		write (1, "pb\n", 3);
	else
		write (1, "pa\n", 3);
}

void	rotate(t_stack *lst)
{
	t_node	*temp;

	if (lst->size > 1)
	{
		temp = lst->head;
		lst->head = lst->head->next;
		lst->tail->next = temp;
		lst->tail = temp;
		lst->tail->next = NULL;
		if (lst->name == 'a')
			write (1, "ra\n", 3);
		else
			write (1, "rb\n", 3);
	}
}

void	reverse_rotate(t_stack *lst)
{
	t_node	*temp1;
	t_node	*temp2;
	size_t	i;

	if (lst->size > 1)
	{
		temp1 = lst->head;
		temp2 = lst->head;
		i = 0;
		while (i < (lst->size - 2))
		{
			temp1 = temp1->next;
			i++;
		}
		lst->head = lst->tail;
		lst->head->next = temp2;
		lst->tail = temp1;
		lst->tail->next = NULL;
		if (lst->name == 'a')
			write (1, "rra\n", 4);
		else
			write (1, "rrb\n", 4);
	}
}

void	rotate_both(t_stack *lst_a, t_stack *lst_b)
{
	t_node	*temp;

	if (lst_a->size > 1 && lst_b->size > 1)
	{
		temp = lst_a->head;
		lst_a->head = lst_a->head->next;
		lst_a->tail->next = temp;
		lst_a->tail = temp;
		lst_a->tail->next = NULL;
		temp = lst_b->head;
		lst_b->head = lst_b->head->next;
		lst_b->tail->next = temp;
		lst_b->tail = temp;
		lst_b->tail->next = NULL;
		write (1, "rr\n", 3);
	}
}
