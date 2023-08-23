/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 21:54:19 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/23 00:57:38 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		printf ("%sError allocating memory\n", RED);
	else if (error == ERROR_TH)
	{
		info->start_time = 1;
		info->dead = 1;
		printf ("%sError creating thread\n", RED);
		close_semaphores(info);
		free(info->pid_philos);
	}
	return (1);
}

int	ft_error_handler_sem(int error, t_info *info)
{
	int	i;

	if (error == ERROR_SEM)
	{
		printf ("%sError creating semaphore\n", RED);
		free(info->pid_philos);
		close_semaphores(info);
	}
	else if (error == ERROR_PID)
	{
		printf ("%sError creating process\n", RED);
		i = 0;
		while (i < info->philo_id)
			kill(info->pid_philos[i++], SIGKILL);
		free(info->pid_philos);
		close_semaphores(info);
		exit(1);
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
		if (ft_atoi(argv[j]) < 1 && j == 5)
			return (ft_error_handler(ERROR_MEALS, NULL));
	}
	return (0);
}
