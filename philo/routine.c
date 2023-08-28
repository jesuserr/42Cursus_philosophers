/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 17:54:38 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/28 12:53:06 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_forks_eat_and_release_forks(t_philo *philo);
void	print_message(t_philo *philo, char *msg);

/* All philos will start with the same starting time since execution */
/* of all threads is stopped until all threads are up and running. */
/* If only one philo is provided, prints message and exits thread. */
/* When a philo dies, all the life cycle is performed but not printed, */
/* if required it can be changed adding an if inside the while. */
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
		grab_forks_eat_and_release_forks(philo);
		print_message(philo, "is sleeping");
		ft_msleep(philo->info->sleep_time);
		print_message(philo, "is thinking");
	}
	return (NULL);
}

/* Depending on the philo position (even or odd), the forks are grabbed */
/* in different order to avoid deadlock. Forks are always released in the */
/* same order, no matter how they were taken. */
/* To optimize the code the last meal time is captured just before eating */
/* and the forks are released asap. Meal counters are only updated if */
/* number of meals has been provided by the user (to save time) */
void	grab_forks_eat_and_release_forks(t_philo *philo)
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
	print_message(philo, "is eating");
	philo->last_meal = get_time_ms();
	ft_msleep(philo->info->eat_time);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	if (philo->info->max_meals != INT_MAX)
	{
		philo->meals++;
		pthread_mutex_lock(&philo->info->meals_mtx);
		philo->info->total_meals++;
		pthread_mutex_unlock(&philo->info->meals_mtx);
	}
}

/* Prints messages only if there are no dead philosophers */
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
