/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 22:43:53 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/16 23:02:46 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitoring(void *arg)
{
	t_info	*info;

	info = (t_info *)arg;
	while (get_time_ms() - info->start_time < 50000)
		ft_msleep(1);
	printf("%ld hello\n", get_time_ms() - info->start_time);
	info->dead = 1;
	return (NULL);
}
