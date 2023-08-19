/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 17:54:38 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/19 00:23:26 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_forks(t_philo *philo);
void	eat_and_release_forks(t_philo *philo);
void	print_message(t_philo *philo, char *msg);

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->info->start_mtx);
	philo->info->active_threads++;
	pthread_mutex_unlock(&philo->info->start_mtx);
	while (philo->info->start_time == 0)
		ft_msleep(1);
	philo->last_meal = philo->info->start_time;
	while (philo->info->dead == 0)
	{
		grab_forks(philo);
		eat_and_release_forks(philo);
		print_message(philo, "is sleeping");
		ft_msleep(philo->info->sleep_time);
		print_message(philo, "is thinking");
	}
	return (NULL);
}

void	print_message(t_philo *philo, char *msg)
{
	if (philo->info->dead == 0)
	{
		pthread_mutex_lock(&philo->info->print_mtx);
		printf("%ld %d %s\n", get_time_ms() - philo->info->start_time, \
			philo->philo_id + 1, msg);
		pthread_mutex_unlock(&philo->info->print_mtx);
	}
}
//printf("%ld \n", get_time_ms() - philo->last_meal);

void	grab_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
	}
	print_message(philo, "has taken a fork");
}

void	eat_and_release_forks(t_philo *philo)
{
	print_message(philo, "is eating");
	philo->last_meal = get_time_ms();
	ft_msleep(philo->info->eat_time);
	philo->meals++;
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}
