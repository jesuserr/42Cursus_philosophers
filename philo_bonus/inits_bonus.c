/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 22:00:16 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/28 17:35:59 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* Fills struct 'info' with the data provided by the user and initializes */
/* all the values. Allocates memory to contain a pid for each philosopher */
int	init_info(int argc, char **argv, t_info *info)
{
	info->nbr_philos = ft_atoi(argv[1]);
	info->die_time = ft_atoi(argv[2]);
	info->eat_time = ft_atoi(argv[3]);
	info->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		info->max_meals = ft_atoi(argv[5]);
	else
		info->max_meals = -1;
	info->pid_philos = malloc(sizeof(pid_t) * info->nbr_philos);
	if (!info->pid_philos)
		return (ft_error_handler(ERROR_MEM, info));
	info->start_time = 0;
	info->meals = 0;
	info->last_meal = 0;
	return (0);
}

/* Inits semaphores for number of forks (same number as philosophers), */
/* printing, death detection and counting number of meals. The last two */
/* semaphores are "set to zero" */
int	init_semaphores(t_info *info)
{
	sem_unlink("forks_sem");
	sem_unlink("print_sem");
	sem_unlink("dead_sem");
	sem_unlink("meals_sem");
	info->forks_sem = sem_open("forks_sem", O_CREAT | O_EXCL, S_IRWXU, \
		info->nbr_philos);
	if (info->forks_sem == SEM_FAILED)
		return (ft_error_handler_sem(ERROR_SEM, info));
	info->print_sem = sem_open("print_sem", O_CREAT | O_EXCL, S_IRWXU, 1);
	if (info->print_sem == SEM_FAILED)
		return (ft_error_handler_sem(ERROR_SEM, info));
	info->dead_sem = sem_open("dead_sem", O_CREAT | O_EXCL, S_IRWXU, 1);
	if (info->dead_sem == SEM_FAILED)
		return (ft_error_handler_sem(ERROR_SEM, info));
	info->meals_sem = sem_open("meals_sem", O_CREAT | O_EXCL, S_IRWXU, 1);
	if (info->meals_sem == SEM_FAILED)
		return (ft_error_handler_sem(ERROR_SEM, info));
	sem_wait(info->dead_sem);
	sem_wait(info->meals_sem);
	return (0);
}

/* If number of meals are provided, it creates a thread to control it. */
/* Detaching the thread allows that after thread termination, its */
/* resources are automatically released back to the system without the need */
/* for another thread to join with the terminated thread */
int	init_meals_monitor(t_info *info)
{
	if (info->max_meals > 0)
	{
		if (pthread_create(&info->meals_monitor, NULL, &nbr_meals_monitor, \
			(void *) info) != 0)
			return (ft_error_handler(ERROR_TH, info));
		pthread_detach(info->meals_monitor);
	}
	return (0);
}

/* It creates a process per each philosopher, the process contains a thread */
/* to control the death of the philosopher and the philosopher life routine. */
/* Main process waits until a notification is received from "dead_sem" */
/* Thread and routine are never back */
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
			info->last_meal = info->start_time;
			if (pthread_create(&info->pid_monitor, NULL, &pid_monitor, \
				(void *) info) != 0)
				return (ft_error_handler(ERROR_TH, info));
			pthread_detach(info->pid_monitor);
			routine(info);
		}
		i++;
	}
	sem_wait(info->dead_sem);
	return (0);
}
