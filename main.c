/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:42:51 by jesuserr          #+#    #+#             */
/*   Updated: 2023/05/10 13:06:04 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_program(int argc, char **argv)
{
	t_node	*node;
	t_stack	*stack_a;
	t_stack	*stack_b;

	stack_a = ft_new_stack(0);
	stack_b = ft_new_stack(stack_a);
	while (argc-- > 1)
	{
		node = ft_new_node(ft_atoi(argv[argc]));
		if (!node)
		{
			ft_total_free(stack_a, stack_b);
			ft_error_handler(ERROR_MALLOC_NODE);
		}
		ft_add_node_front(stack_a, node);
	}
	stack_parsing(stack_a);
	sort_stack(stack_a, stack_b);
	ft_total_free(stack_a, stack_b);
}

int	main(int argc, char **argv)
{
	if (argc > 1)
	{
		detect_no_numbers(argc, argv);
		detect_duplicates_limits_and_order(argc, argv);
		init_program(argc, argv);
	}	
	return (0);
}
