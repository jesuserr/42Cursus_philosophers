/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:16:57 by jesuserr          #+#    #+#             */
/*   Updated: 2023/05/08 08:40:22 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_error_handler(int error)
{
	if (error == ERROR)
		write (2, "Error\n", 6);
	else if (error == NUMS_SORTED)
		exit(EXIT_SUCCESS);
	else if (error == ERROR_MALLOC_STACK_A)
		write (1, RED"Malloc Error Stack A\n", 28);
	else if (error == ERROR_MALLOC_STACK_B)
		write (1, RED"Malloc Error Stack B\n", 28);
	else if (error == ERROR_MALLOC_NODE)
		write (1, RED"Malloc Error On Node Creation\n", 37);
	exit(EXIT_FAILURE);
}

void	detect_no_numbers(int argc, char **argv)
{
	int		i;
	char	c;

	while (argc > 1)
	{
		argc--;
		i = 0;
		if (argv[argc][0] == '\0')
			ft_error_handler(ERROR);
		while (argv[argc][i] != '\0')
		{
			c = argv[argc][i];
			if (i == 0)
			{
				if (!(ft_isdigit(c) || (c == '-' && ft_isdigit(argv[argc][1]))
					|| (c == '+' && ft_isdigit(argv[argc][1]))))
					ft_error_handler(ERROR);
			}
			else
				if (!(ft_isdigit(c)))
					ft_error_handler(ERROR);
			i++;
		}		
	}	
}

void	detect_duplicates_limits_and_order(int argc, char **argv)
{
	int	i;
	int	j;
	int	k;

	i = 1;
	k = 0;
	while (i < (argc - 1))
	{
		j = i + 1;
		while (j < (argc))
		{
			if (ft_atoi(argv[i]) == ft_atoi(argv[j]))
				ft_error_handler(ERROR);
			if ((ft_atoi(argv[i]) > ft_atoi(argv[j])) && k == 0)
				k = 1;
			j++;
		}
		i++;
	}
	while (argc-- > 1)
		if ((ft_atoi(argv[argc]) > INT_MAX) || (ft_atoi(argv[argc]) < INT_MIN))
			ft_error_handler(ERROR);
	if (k == 0)
		ft_error_handler(NUMS_SORTED);
}
