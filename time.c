/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:22:18 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/16 16:42:05 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	start;
	long			milisecs;

	gettimeofday(&start, NULL);
	milisecs = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	return (milisecs);
}

void	ft_msleep(long milisecs)
{
	long	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < milisecs)
		usleep(milisecs / 100);
}
