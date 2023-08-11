/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:10:29 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/11 11:51:26 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error_handler(int error)
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
	return (1);
}

int	check_args(int argc, char **argv)
{
	int		i;
	int		j;

	if (argc < 5 || argc > 6)
		return (ft_error_handler(ERROR_ARGS));
	j = 0;
	while (++j <= argc - 1)
	{
		i = 0;
		while (argv[j][i] != '\0')
			if (!(ft_is_digit(argv[j][i++])))
				return (ft_error_handler(ERROR_FORMAT));
		if (ft_atoi(argv[j]) > INT_MAX)
			return (ft_error_handler(ERROR_FORMAT));
		if (ft_atoi(argv[j]) < 1 && j == 1)
			return (ft_error_handler(ERROR_PHILO));
		if (ft_atoi(argv[j]) < 60 && (j >= 2 && j <= 4))
		{
			printf ("%sArgument %d ", RED, j);
			return (ft_error_handler(ERROR_TIMES));
		}
		if (ft_atoi(argv[j]) < 1 && j == 5)
			return (ft_error_handler(ERROR_MEALS));
	}
	return (0);
}
