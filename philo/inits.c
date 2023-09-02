/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 17:47:49 by jesuserr          #+#    #+#             */
/*   Updated: 2023/09/02 20:49:14 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Fill in struct 'info' with the data provided by the user and */
/* initialize values. 'info' will contain all philos as an array */
void	init_info(int argc, char **argv, t_info *info)
{
	info->nbr_philos = ft_atoi(argv[1]);
	info->die_time = ft_atoi(argv[2]);
	info->eat_time = ft_atoi(argv[3]);
	info->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		info->max_meals = ft_atoi(argv[5]);
	else
		info->max_meals = INT_MAX;
	info->forks_mtx = NULL;
	info->philos_array = NULL;
	info->philos_th = NULL;
	info->total_meals = 0;
	info->dead = 0;
	info->active_threads = 0;
	info->start_time = 0;
}

/* Init an array of mutexes (one per fork) */
/* Init also mutexes for printing, starting and counting total meals */
int	init_mutexes(t_info *info)
{
	int				i;
	pthread_mutex_t	*mutex;

	i = 0;
	mutex = malloc(sizeof(pthread_mutex_t) * info->nbr_philos);
	if (!mutex)
		return (ft_error_handler(ERROR_MEM, info));
	while (i < info->nbr_philos)
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	info->forks_mtx = mutex;
	pthread_mutex_init(&info->print_mtx, NULL);
	pthread_mutex_init(&info->start_mtx, NULL);
	pthread_mutex_init(&info->meals_mtx, NULL);
	return (0);
}

/* Init information for each one of the philosophers */
/* Each philo contains a pointer to the 'info' struct */
int	init_philos(t_info *info)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * info->nbr_philos);
	if (!philos)
		return (ft_error_handler(ERROR_MEM, info));
	i = 0;
	while (i < info->nbr_philos)
	{
		philos[i].philo_id = i;
		philos[i].meals = 0;
		philos[i].info = info;
		philos[i].right_fork = &info->forks_mtx[i];
		philos[i].left_fork = &info->forks_mtx[i + 1];
		i++;
	}
	philos[i - 1].left_fork = &info->forks_mtx[0];
	info->philos_array = philos;
	return (0);
}

/* Initialize an array of threads (one per philo) and detach all of them */
/* Initialize another thread for monitoring all philos */
/* Main process waits until completion of monitor thread */
int	init_threads(t_info *info)
{
	int			i;
	pthread_t	*philos;

	i = 0;
	philos = malloc(sizeof(pthread_t) * info->nbr_philos);
	if (!philos)
		return (ft_error_handler(ERROR_MEM, info));
	info->philos_th = philos;
	while (i < info->nbr_philos)
	{
		if (pthread_create(&philos[i], NULL, &routine, \
		(void *) &info->philos_array[i]) != 0)
			return (ft_error_handler(ERROR_TH, info));
		pthread_detach(philos[i]);
		i++;
	}
	if (pthread_create(&info->monitor, NULL, &monitoring, (void *) info) != 0)
		return (ft_error_handler(ERROR_TH, info));
	pthread_join(info->monitor, NULL);
	return (0);
}
