/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 22:43:53 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/19 12:27:55 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitoring(void *arg)
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
			if ((get_time_ms() - info->philos_list[i].last_meal) > info->die_time)
			{
				info->dead = 1;
				pthread_mutex_lock(&info->print_mtx);
				printf("%ld %d %s\n", get_time_ms() - info->start_time, \
					info->philos_list[i].philo_id + 1, "died");
				break ;
			}
			i++;
		}
	}
	return (NULL);
}
