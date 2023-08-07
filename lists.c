/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:29:48 by jesuserr          #+#    #+#             */
/*   Updated: 2023/05/10 13:06:19 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*ft_new_stack(t_stack *lst)
{
	t_stack	*new;
	char	name;

	if (!lst)
		name = 'a';
	else
		name = 'b';
	new = (t_stack *)malloc(sizeof(t_stack));
	if (!new && !lst)
		ft_error_handler(ERROR_MALLOC_STACK_A);
	else if (!new && lst)
	{
		free(lst);
		ft_error_handler(ERROR_MALLOC_STACK_B);
	}
	new->head = NULL;
	new->tail = NULL;
	new->size = 0;
	new->name = name;
	return (new);
}

t_node	*ft_new_node(int number)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return (0);
	new->value = number;
	new->next = NULL;
	new->parse = 0;
	return (new);
}

void	ft_add_node_front(t_stack *lst, t_node *new)
{
	if (!new)
		return ;
	lst->size++;
	if (!lst->head)
	{
		lst->head = new;
		lst->tail = new;
		new->next = NULL;
		return ;
	}
	new->next = lst->head;
	lst->head = new;
}
