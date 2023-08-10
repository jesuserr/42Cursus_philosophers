/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:05:04 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/10 19:41:48 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_info *info)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * info->nbr_philos);
	if (!philos)
	{
		// free mutex
		ft_error_handler(ERROR_MEM);
	}
	i = 0;
	while (i < info->nbr_philos)
	{
		philos[i].philo_id = i;
		philos[i].meals = 0;
		philos[i].last_meal = get_time_ms();
		i++;
	}
	info->philo_list = philos;
}

/* Fills info struct with the info provided by the user */
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
}

/* Initializes an array of mutexes (one mutex per fork/philo) */
/* Initializes also one mutex for printing */
void	init_mutexes(t_info *info)
{
	int				i;
	pthread_mutex_t	*mutex;

	i = 0;
	mutex = malloc(sizeof(pthread_mutex_t) * info->nbr_philos);
	if (!mutex)
		ft_error_handler(ERROR_MEM);
	while (i < info->nbr_philos)
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	info->forks_mtx = mutex;
	pthread_mutex_init(&info->print_mtx, NULL);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc < 5 || argc > 6)
		ft_error_handler(ERROR_ARGS);
	check_args(argc, argv);
	init_info(argc, argv, &info);
	init_mutexes(&info);
	init_philos(&info);
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
*/