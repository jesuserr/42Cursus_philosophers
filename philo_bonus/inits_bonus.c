/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 22:00:16 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/24 17:40:57 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* Fill in struct 'info' with the data provided by the user and */
/* initialize values. */
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
	info->dead = 0;
	info->start_time = 0;
	info->meals = 0;
	info->last_meal = 0;
	return (0);
}

/* Init semaphores for number of forks, printing, starting and */
/* counting total meals */
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

int	init_overall_monitor(t_info *info)
{
	if (pthread_create(&info->gen_monitor, NULL, &overall_monitor, \
		(void *) info) != 0)
		return (ft_error_handler(ERROR_TH, info));
	return (0);
}

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
			routine(info);
		}
		i++;
	}
	sem_wait(info->dead_sem);
	pthread_join(info->gen_monitor, NULL);
	return (0);
}

// mirar como limpiar en caso de que falle la creación del 'n' 
// hilo en pid_monitor (movida)