/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 21:48:08 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/24 21:27:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* Close & unlink all semaphores */
void	close_semaphores(t_info *info)
{
	sem_close(info->print_sem);
	sem_unlink("print_sem");
	sem_close(info->forks_sem);
	sem_unlink("forks_sem");
	sem_close(info->meals_sem);
	sem_unlink("meals_sem");
	sem_close(info->dead_sem);
	sem_unlink("dead_sem");
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
	if (init_overall_monitor(&info))
		return (1);
	if (init_processes(&info))
		return (1);
	close_semaphores(&info);
	free(info.pid_philos);
	return (0);
}

// make bonus && valgrind --leak-check=full -s ./philo_bonus 6 60 60 60 56