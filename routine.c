/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 17:54:38 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/12 22:07:01 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	philo;

	philo = *(t_philo *)arg;
	pthread_mutex_lock(&philo.info->print_mtx);
	printf("Hello from thread: %d\n", philo.philo_id);
	printf("Number of philosophers: %d\n", philo.info->nbr_philos);
	printf("Time: %lu\n", get_time_us() - philo.last_meal);
	pthread_mutex_unlock(&philo.info->print_mtx);
	return (NULL);
}
