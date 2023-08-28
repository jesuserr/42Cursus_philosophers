/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:05:04 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/28 12:18:09 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Wait for finalization of all the threads */
/* Print info if number of meals have been specified and nobody died */
void	join_threads(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nbr_philos)
	{
		pthread_join(info->philos_th[i], NULL);
		i++;
	}
	if ((info->max_meals != INT_MAX) && (info->dead == 0))
	{
		pthread_mutex_lock(&info->print_mtx);
		printf("Each philosopher ate: %d times\n", info->max_meals);
		printf("Total served meals: %d\n", info->total_meals);
		pthread_mutex_unlock(&info->print_mtx);
	}
}

/* Unlock & destroy all mutexes */
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
	pthread_mutex_unlock(&info->start_mtx);
	pthread_mutex_destroy(&info->start_mtx);
	pthread_mutex_unlock(&info->meals_mtx);
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
	join_threads(&info);
	destroy_mutexes(&info);
	free_memory(&info);
	return (0);
}
