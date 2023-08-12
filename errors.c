/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:10:29 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/12 18:56:38 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error_handler(int error, t_info *info)
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
	{
		printf ("%sError allocating memory\n", RED);
		free_memory(info);
	}
	return (1);
}

void	free_memory(t_info *info)
{
	if (info->philo_list)
		free(info->philo_list);
	if (info->philos_t)
		free(info->philos_t);
	if (info->forks_mtx)
		free(info->forks_mtx);
}

int	check_args(int argc, char **argv)
{
	int		i;
	int		j;

	if (argc < 5 || argc > 6)
		return (ft_error_handler(ERROR_ARGS, NULL));
	j = 0;
	while (++j <= argc - 1)
	{
		i = 0;
		while (argv[j][i] != '\0')
			if (!(ft_is_digit(argv[j][i++])))
				return (ft_error_handler(ERROR_FORMAT, NULL));
		if (ft_atoi(argv[j]) > INT_MAX)
			return (ft_error_handler(ERROR_FORMAT, NULL));
		if (ft_atoi(argv[j]) < 1 && j == 1)
			return (ft_error_handler(ERROR_PHILO, NULL));
		if (ft_atoi(argv[j]) < 60 && (j >= 2 && j <= 4))
		{
			printf ("%sArgument %d ", RED, j);
			return (ft_error_handler(ERROR_TIMES, NULL));
		}
		if (ft_atoi(argv[j]) < 1 && j == 5)
			return (ft_error_handler(ERROR_MEALS, NULL));
	}
	return (0);
}
