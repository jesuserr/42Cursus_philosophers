/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 21:48:08 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/23 00:55:47 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* Print info if number of meals have been specified and */
/* number of philos is greater than 1 and nobody died */
void	join_threads(t_info *info)
{
	if ((info->max_meals > 0 && info->max_meals < INT_MAX) && \
	(info->nbr_philos > 1) && (info->dead == 0))
	{
		sem_wait(info->print_sem);
		printf("Each philosopher ate: %d times\n", info->max_meals);
		printf("Total served meals: %d\n", info->total_meals);
		sem_post(info->print_sem);
	}
}

/* Close & unlink all semaphores */
void	close_semaphores(t_info *info)
{
	sem_close(info->print_sem);
	sem_unlink("print_sem");
	sem_close(info->forks_sem);
	sem_unlink("forks_sem");
	sem_close(info->meals_sem);
	sem_unlink("meals_sem");
	sem_close(info->start_sem);
	sem_unlink("start_sem");
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (check_args(argc, argv))
		return (1);
	if (init_info(argc, argv, &info))
		return (1);
	if (init_semaphores(&info))
		return (1);
	if (init_processes(&info))
		return (1);
	//if (init_monitor(&info))
	//	return (1);
	//join_threads(&info);
	close_semaphores(&info);
	free(info.pid_philos);
	return (0);
}

// make bonus && valgrind --leak-check=full -s ./philo_bonus 6 60 60 60 56