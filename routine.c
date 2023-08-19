/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 17:54:38 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/19 12:37:17 by codespace        ###   ########.fr       */
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
	if (philo->info->nbr_philos == 1)
	{
		print_message(philo, "has taken a fork");
		return (NULL);
	}
	while (philo->info->dead == 0 && philo->meals < philo->info->max_meals)
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
	philo->last_meal = get_time_ms();
	print_message(philo, "is eating");
	ft_msleep(philo->info->eat_time);
	pthread_mutex_lock(&philo->info->meals_mtx);
	philo->info->total_meals++;
	pthread_mutex_unlock(&philo->info->meals_mtx);
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
