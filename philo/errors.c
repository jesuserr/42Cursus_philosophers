/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:10:29 by jesuserr          #+#    #+#             */
/*   Updated: 2023/09/10 20:10:35 by jesuserr         ###   ########.fr       */
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
		printf ("%sInvalid meals number - range from 1 to 2147483646\n", RED);
	else if (error == ERROR_MEM)
	{
		printf ("%sError allocating memory\n", RED);
		free_memory(info);
	}
	else if (error == ERROR_TH)
	{
		info->start_time = 1;
		info->dead = 1;
		ft_msleep(info->eat_time + info->sleep_time);
		printf ("%sError creating thread\n", RED);
		destroy_mutexes(info);
		free_memory(info);
	}
	return (1);
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
		if ((ft_atoi(argv[j]) < 1 || ft_atoi(argv[j]) > MAX_PHILOS) && j == 1)
			return (ft_error_handler(ERROR_PHILO, NULL));
		if (ft_atoi(argv[j]) < MIN_TIME && (j >= 2 && j <= 4))
		{
			printf ("%sArgument %d ", RED, j);
			return (ft_error_handler(ERROR_TIMES, NULL));
		}
		if ((ft_atoi(argv[j]) < 1 || ft_atoi(argv[j]) > INT_MAX - 1) && j == 5)
			return (ft_error_handler(ERROR_MEALS, NULL));
	}
	return (0);
}
