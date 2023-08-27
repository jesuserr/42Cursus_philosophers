/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 21:48:08 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/27 13:25:03 by jesuserr         ###   ########.fr       */
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

/* Kills all child processes. SIGTERM preferred over SIGKILL since it */
/* kills the process politely */
void	kill_processes(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nbr_philos)
		kill(info->pid_philos[i++], SIGTERM);
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
	if (init_meals_monitor(&info))
		return (1);
	if (init_processes(&info))
		return (1);
	kill_processes(&info);
	close_semaphores(&info);
	free(info.pid_philos);
	return (0);
}
