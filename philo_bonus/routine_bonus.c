/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:22:07 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/27 13:08:25 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_message(t_info *info, char *msg);

/* Introduces a small delay on even philosophers to avoid deadlocks. */
/* Routine runs forever until the process is killed in the main program or */
/* the number of meals are reached and then exits. */
/* When meals are reached, pilosophers are left in 'thinking' state, this */
/* can be modified changing the position of the if */
void	*routine(t_info *info)
{
	if (info->philo_id % 2 == 0)
		ft_msleep(2);
	while (1)
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
			sem_post(info->meals_sem);
			exit(0);
		}
	}
	return (NULL);
}

void	print_message(t_info *info, char *msg)
{
	sem_wait(info->print_sem);
	printf("%ld %d %s\n", get_time_ms() - info->start_time, \
		info->philo_id + 1, msg);
	sem_post(info->print_sem);
}
