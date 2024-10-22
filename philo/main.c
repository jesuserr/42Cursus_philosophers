/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:05:04 by jesuserr          #+#    #+#             */
/*   Updated: 2023/09/10 20:08:39 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Destroy all mutexes */
/* Note: Previously the mutexes where unlocked before destroy them */
/* but it was removed since it caused an error */
void	destroy_mutexes(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nbr_philos)
	{
		pthread_mutex_destroy(&info->forks_mtx[i]);
		i++;
	}
	pthread_mutex_destroy(&info->print_mtx);
	pthread_mutex_destroy(&info->start_mtx);
	pthread_mutex_destroy(&info->meals_mtx);
}

void	free_memory(t_info *info)
{
	if (info->philos_array)
		free(info->philos_array);
	if (info->philos_th)
		free(info->philos_th);
	if (info->forks_mtx)
		free(info->forks_mtx);
}

/* The purpose of the sleep is to give time to all the threads to finish */
/* their vital cycles, before destroying the mutexes and finishing the */
/* program execution. This is because now all the threads are detached */
/* instead of joined */
int	main(int argc, char **argv)
{
	t_info	info;

	if (check_args(argc, argv))
		return (1);
	init_info(argc, argv, &info);
	if (init_mutexes(&info))
		return (1);
	if (init_philos(&info))
		return (1);
	if (init_threads(&info))
		return (1);
	ft_msleep(info.eat_time + info.sleep_time);
	if ((info.max_meals != INT_MAX) && (info.dead == 0))
	{
		pthread_mutex_lock(&info.print_mtx);
		printf("Each philosopher ate: %d times\n", info.max_meals);
		printf("Total served meals: %d\n", info.total_meals);
		pthread_mutex_unlock(&info.print_mtx);
	}
	destroy_mutexes(&info);
	free_memory(&info);
	return (0);
}
