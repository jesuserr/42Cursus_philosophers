/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:37:45 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/24 21:27:37 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*overall_monitor(void *arg)
{
	t_info	*info;
	int		i;

	info = (t_info *)arg;
	i = 0;
	if (info->max_meals > 0 && info->max_meals < INT_MAX)
	{
		while (i < info->nbr_philos)
		{
			sem_wait(info->meals_sem);
			i++;
		}
		sem_post(info->dead_sem);
	}
	return (NULL);
}

void	*pid_monitor(void *arg)
{
	t_info	*info;

	info = (t_info *)arg;
	while (info->dead == 0)
	{
		if ((get_time_ms() - info->last_meal) > info->die_time)
		{
			info->dead = 1;
			sem_wait(info->print_sem);
			printf("%ld %d %s\n", get_time_ms() - info->start_time, \
				info->philo_id + 1, "died");
			sem_post(info->dead_sem);
			kill_processes(info);
		}
	}
	return (NULL);
}

void	kill_processes(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nbr_philos)
		kill(info->pid_philos[i++], SIGINT);
}
