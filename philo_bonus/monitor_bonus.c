/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:37:45 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/28 17:40:27 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* Receives a notification from "meals_sem" every time a philosopher has */
/* reached the number of required meals. Once all philosophers have eaten */
/* the required times, activates "dead_sem" and dies */
void	*nbr_meals_monitor(void *arg)
{
	t_info	*info;
	int		i;

	info = (t_info *)arg;
	i = 0;
	while (i < info->nbr_philos)
	{
		sem_wait(info->meals_sem);
		i++;
	}
	sem_post(info->dead_sem);
	return (NULL);
}

/* Detects when the associated philosopher has died from starvation and */
/* then activates "dead_sem" and dies. Keeps the print semaphore locked to */
/* avoid further printing from another processes */
void	*pid_monitor(void *arg)
{
	t_info	*info;

	info = (t_info *)arg;
	while (1)
	{
		if ((get_time_ms() - info->last_meal) > info->die_time)
		{
			sem_wait(info->print_sem);
			printf("%ld %d %s\n", get_time_ms() - info->start_time, \
				info->philo_id + 1, "died");
			sem_post(info->dead_sem);
			break ;
		}
	}
	return (NULL);
}
