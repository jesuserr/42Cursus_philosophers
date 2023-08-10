/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:10:29 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/10 17:32:25 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error_handler(int error)
{
	if (error == ERROR_ARGS)
		printf ("%sInvalid number of arguments\n", RED);
	else if (error == ERROR_FORMAT)
		printf ("%sInvalid format of arguments\n", RED);
	else if (error == ERROR_PHILO)
		printf ("%sInvalid number of philosophers\n", RED);
	else if (error == ERROR_TIMES)
		printf ("%sInvalid time - minimum 60 ms\n", RED);
	else if (error == ERROR_MEALS)
		printf ("%sInvalid number of meals - minimum 1\n", RED);
	else if (error == ERROR_MEM)
		printf ("%sError allocating memory\n", RED);
	exit(EXIT_FAILURE);
}

void	check_args(int argc, char **argv)
{
	int		i;
	int		j;

	j = 1;
	while (j <= argc - 1)
	{
		i = 0;
		while (argv[j][i] != '\0')
			if (!(ft_is_digit(argv[j][i++])))
				ft_error_handler(ERROR_FORMAT);
		if (ft_atoi(argv[j]) > INT_MAX)
			ft_error_handler(ERROR_FORMAT);
		if (ft_atoi(argv[j]) < 1 && j == 1)
			ft_error_handler(ERROR_PHILO);
		if (ft_atoi(argv[j]) < 60 && (j >= 2 && j <= 4))
		{
			printf ("%sArgument %d ", RED, j);
			ft_error_handler(ERROR_TIMES);
		}
		if (ft_atoi(argv[j]) < 1 && j == 5)
			ft_error_handler(ERROR_MEALS);
		j++;
	}
}
