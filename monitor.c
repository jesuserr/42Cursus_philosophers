/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 22:43:53 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/18 13:22:19 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitoring(void *arg)
{
	t_info	*info;

	info = (t_info *)arg;
	while (info->active_threads != info->nbr_philos)
		ft_msleep(1);
	info->start_time = get_time_ms();
	while (1)
		;
	return (NULL);
}
