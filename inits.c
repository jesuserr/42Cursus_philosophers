/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 17:47:49 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/12 18:56:11 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Fills struct 'info' with the info provided by the user */
void	init_info(int argc, char **argv, t_info *info)
{
	info->nbr_philos = ft_atoi(argv[1]);
	info->die_time = ft_atoi(argv[2]);
	info->eat_time = ft_atoi(argv[3]);
	info->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		info->max_meals = ft_atoi(argv[5]);
	else
		info->max_meals = -1;
	info->forks_mtx = NULL;
	info->philo_list = NULL;
	info->philos_t = NULL;
}

/* Inits information for each one of the philosophers */
/* IN PROGRESS */
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
		philos[i].last_meal = get_time_ms();
		i++;
	}
	info->philo_list = philos;
	return (0);
}

/* Initializes an array of mutexes (one mutex per fork/philo) */
/* Initializes also one mutex for printing */
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
	return (0);
}

/* Initializes an array of threads (one per philo) */
int	init_threads(t_info *info)
{
	int			i;
	pthread_t	*philos;

	i = 0;
	philos = malloc(sizeof(pthread_t) * info->nbr_philos);
	if (!philos)
		return (ft_error_handler(ERROR_MEM, info));
	while (i < info->nbr_philos)
	{
		pthread_create(&philos[i], NULL, &routine, NULL);
		i++;
	}
	info->philos_t = philos;
	return (0);
}
