/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 17:54:38 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/14 21:32:11 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_forks(t_philo *philo);
void	eat_and_release_forks(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		grab_forks(philo);
		eat_and_release_forks(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	grab_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&philo->info->print_mtx);
		printf("%ld %d has taken a fork\n", get_time_ms() - philo->info->start_time, philo->philo_id + 1);
		pthread_mutex_unlock(&philo->info->print_mtx);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->info->print_mtx);
		printf("%ld %d has taken a fork\n", get_time_ms() - philo->info->start_time, philo->philo_id + 1);
		pthread_mutex_unlock(&philo->info->print_mtx);
		pthread_mutex_lock(philo->left_fork);
	}
	pthread_mutex_lock(&philo->info->print_mtx);
	printf("%ld %d has taken a fork\n", get_time_ms() - philo->info->start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->info->print_mtx);
}

void	eat_and_release_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->print_mtx);
	printf("%ld %d is eating\n", get_time_ms() - philo->info->start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->info->print_mtx);
	philo->meals++;
	ft_msleep(philo->info->eat_time);
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

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->print_mtx);
	printf("%ld %d is sleeping\n", get_time_ms() - philo->info->start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->info->print_mtx);
	ft_msleep(philo->info->sleep_time);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->print_mtx);
	printf("%ld %d is thinking\n", get_time_ms() - philo->info->start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->info->print_mtx);
}

//printf("%ld %d is eating\n", get_time_ms() - philo->info->start_time, philo->philo_id + 1);
		//ft_msleep(philo->info->eat_time);
		//pthread_mutex_unlock(philo->left_fork);
		//pthread_mutex_unlock(philo->right_fork);
		//printf("%ld %d is sleeping\n", get_time_ms() - philo->info->start_time, philo->philo_id + 1);
		//ft_msleep(philo->info->sleep_time);