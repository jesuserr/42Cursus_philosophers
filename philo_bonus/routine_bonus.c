/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:22:07 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/24 17:41:13 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_message(t_info *info, char *msg);

/* All philos will start with the same starting time since execution */
/* of all threads is stopped until all threads are up and running. */
/* If only one philo is provided, prints message and exits thread. */
/* When a philo dies, all the life cycle is performed but not printed, */
/* if required it can be changed adding an if inside the while. */ 
void	*routine(t_info *info)
{
	if (info->philo_id % 2 == 0)
		ft_msleep(2);
	while (info->dead == 0)
	{
		sem_wait(info->forks_sem);
		print_message(info, "has taken a fork");
		sem_wait(info->forks_sem);
		print_message(info, "has taken a fork");
		info->last_meal = get_time_ms();
		print_message(info, "is eating");
		ft_msleep(info->eat_time);
		info->meals++;
		sem_post(info->forks_sem);
		sem_post(info->forks_sem);
		print_message(info, "is sleeping");
		ft_msleep(info->sleep_time);
		print_message(info, "is thinking");
		if (info->meals == info->max_meals)
		{
			info->dead = 1;
			sem_post(info->meals_sem);
			exit(0);
		}
	}
	return (NULL);
}

/* Prints messages only if there are no dead philosophers */
void	print_message(t_info *info, char *msg)
{
	if (info->dead == 0)
	{
		sem_wait(info->print_sem);
		printf("%ld %d %s\n", get_time_ms() - info->start_time, \
			info->philo_id + 1, msg);
		sem_post(info->print_sem);
	}
}
