/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:36:50 by jesuserr          #+#    #+#             */
/*   Updated: 2023/05/01 15:54:51 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

long	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str [i] == ' ' || (str [i] >= '\t' && str [i] <= '\r'))
		i++;
	if (str [i] == '-')
	{
		sign = -sign;
		i++;
	}
	else if (str [i] == '+')
		i++;
	while (str [i] >= '0' && str [i] <= '9')
	{
		result = (result * 10) + str [i] - '0';
		i++;
	}
	return (result * sign);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	ft_total_free(t_stack *lst_a, t_stack *lst_b)
{
	t_node	*temp;

	while (lst_a->head)
	{
		temp = lst_a->head->next;
		free (lst_a->head);
		lst_a->head = temp;
	}
	while (lst_b->head)
	{
		temp = lst_b->head->next;
		free (lst_b->head);
		lst_b->head = temp;
	}
	free (lst_a);
	free (lst_b);
}
