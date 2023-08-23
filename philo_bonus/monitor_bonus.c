/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:37:45 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/23 16:33:16 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*overall_monitor(void *arg)
{
	t_info	*info;

	info = (t_info *)arg;
	sem_wait(info->dead_sem);
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
		}
	}
	return (NULL);
}

/* Print mutex remains locked to avoid further printings */
/* info->dead is the flag that stops everything */
/* void	execute_death(t_info *info, int i)
{
	info->dead = 1;
	pthread_mutex_lock(&info->print_mtx);
	printf("%ld %d %s\n", get_time_ms() - info->start_time, \
	info->philos_array[i].philo_id + 1, "died");
} */

/* Waits for all the threads to be active in order to apply same starting */
/* time to all of them. Waits 10 ms before starting monitoring to avoid */
/* false positives. */
/* If number of meals are reached, finishes monitoring execution. */
/* If philosopher dies, activates flag to warn all philo threads, */
/* prints message and finishes monitoring execution. */
/* void	*monitoring(void *arg)
{
	t_info	*info;
	int		i;

	info = (t_info *)arg;
	while (info->active_threads != info->nbr_philos)
		ft_msleep(1);
	info->start_time = get_time_ms();
	ft_msleep(10);
	while (info->dead == 0)
	{
		i = 0;
		while (i < info->nbr_philos)
		{
			if (info->total_meals == (info->nbr_philos * info->max_meals))
				return (NULL);
			if ((get_time_ms() - info->philos_array[i].last_meal) > \
			info->die_time)
			{
				execute_death(info, i);
				break ;
			}
			i++;
		}
	}
	return (NULL);
}
 */