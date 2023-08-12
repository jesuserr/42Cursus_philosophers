/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:22:18 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/12 16:00:29 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	start;
	long			micros;

	gettimeofday(&start, NULL);
	micros = (start.tv_sec * 1000000) + start.tv_usec;
	return (micros / 1000);
}

long	get_time_us(void)
{
	struct timeval	start;
	long			micros;

	gettimeofday(&start, NULL);
	micros = (start.tv_sec * 1000000) + start.tv_usec;
	return (micros);
}

void	ft_usleep(long microsecs)
{
	long	start;

	start = get_time_us();
	while ((get_time_us() - start) < microsecs)
		;
}

void	ft_msleep(long milisecs)
{
	long	start;

	start = get_time_us();
	while (((get_time_us() - start) / 1000) < milisecs)
		;
}
