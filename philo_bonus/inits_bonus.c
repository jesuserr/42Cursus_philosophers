/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 22:00:16 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/23 00:59:58 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* Fill in struct 'info' with the data provided by the user and */
/* initialize values. ***'info' will contain all philos as an array*** */
int	init_info(int argc, char **argv, t_info *info)
{
	info->nbr_philos = ft_atoi(argv[1]);
	info->die_time = ft_atoi(argv[2]);
	info->eat_time = ft_atoi(argv[3]);
	info->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		info->max_meals = ft_atoi(argv[5]);
	else
		info->max_meals = INT_MAX;
	info->pid_philos = malloc(sizeof(pid_t) * info->nbr_philos);
	if (!info->pid_philos)
		return (ft_error_handler(ERROR_MEM, info));
	info->total_meals = 0;
	info->dead = 0;
	info->active_processes = 0;
	info->start_time = 0;
	info->meals = 0;
	return (0);
}

/* Init semaphores for number of forks, printing, starting and */
/* counting total meals */
int	init_semaphores(t_info *info)
{
	sem_unlink("forks_sem");
	sem_unlink("print_sem");
	sem_unlink("start_sem");
	sem_unlink("meals_sem");
	info->forks_sem = sem_open("forks_sem", O_CREAT | O_EXCL, S_IRWXU, \
		info->nbr_philos);
	if (info->forks_sem == SEM_FAILED)
		return (ft_error_handler_sem(ERROR_SEM, info));
	info->print_sem = sem_open("print_sem", O_CREAT | O_EXCL, S_IRWXU, 1);
	if (info->print_sem == SEM_FAILED)
		return (ft_error_handler_sem(ERROR_SEM, info));
	info->start_sem = sem_open("start_sem", O_CREAT | O_EXCL, S_IRWXU, 1);
	if (info->start_sem == SEM_FAILED)
		return (ft_error_handler_sem(ERROR_SEM, info));
	info->meals_sem = sem_open("meals_sem", O_CREAT | O_EXCL, S_IRWXU, 1);
	if (info->meals_sem == SEM_FAILED)
		return (ft_error_handler_sem(ERROR_SEM, info));
	return (0);
}

/* Initialize thread for monitoring all philos processes */
/* int	init_monitor(t_info *info)
{
	if (pthread_create(&info->monitor, NULL, &monitoring, (void *) info) != 0)
		return (ft_error_handler(ERROR_TH, info));
	pthread_join(info->monitor, NULL);
	return (0);
} */

int	init_processes(t_info *info)
{
	int	i;

	i = 0;
	info->start_time = get_time_ms();
	while (i < info->nbr_philos)
	{
		info->philo_id = i;
		info->pid_philos[i] = fork();
		if (info->pid_philos[i] == -1)
			ft_error_handler_sem(ERROR_PID, info);
		if (info->pid_philos[i] == 0)
		{
			sem_wait(info->print_sem);
			printf("hello from philo: %d\n", i);
			printf("%lu\n", info->start_time);
			sem_post(info->print_sem);
			sleep (5);
			return (0);
		}
		i++;
	}
	printf("hello from parent\n");
	return (0);
}
