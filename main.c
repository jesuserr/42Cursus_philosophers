/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:05:04 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/12 18:56:29 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Unlock & destroy array of mutexes (one mutex per fork/philo) */
/* Verify before project completion that unlock is needed */
void	destroy_mutexes(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nbr_philos)
	{
		pthread_mutex_unlock(&info->forks_mtx[i]);
		pthread_mutex_destroy(&info->forks_mtx[i]);
		i++;
	}
	pthread_mutex_unlock(&info->print_mtx);
	pthread_mutex_destroy(&info->print_mtx);
}

void	join_threads(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nbr_philos)
	{
		pthread_join(info->philos_t[i], NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (check_args(argc, argv))
		return (1);
	init_info(argc, argv, &info);
	if (init_philos(&info))
		return (1);
	if (init_mutexes(&info))
		return (1);
	if (init_threads(&info))
		return (1);
	join_threads(&info);
	destroy_mutexes(&info);
	free_memory(&info);
	return (0);
}

/*
printf("\n%p", &mutex[i]);
printf("\n%p", &info->print_mtx);
unsigned long a = get_time_ms();
	unsigned long b = get_time_us();
	//printf("\n%lu", get_time());
	//printf("%d", info.philo_list->philo_id);
	//printf("%d", info.philo_list[5].philo_id);
	//usleep(100000);
	usleep(10000);
	printf("\n%lu ms\n", get_time_ms() - a);
	printf("\n%lu us\n", get_time_us() - b);
	printf("\n%ld: ", info.philo_list[0].last_meal);
	printf("\n%ld: ", info.philo_list[9].last_meal);
	make && valgrind --leak-check=full -s ./philo 100 60 60 60 56

	long a = get_time_ms();
	//ft_usleep(333);
	//ft_msleep(5);
	usleep(5000);
	printf("%lu", get_time_ms() - a);
*/