/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:22:18 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/10 19:42:06 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	static struct timeval	start;
	long					micros;

	gettimeofday(&start, NULL);
	micros = (start.tv_sec * 1000000) + start.tv_usec;
	return (micros / 1000);
}

long	get_time_us(void)
{
	static struct timeval	start;
	long					micros;

	gettimeofday(&start, NULL);
	micros = (start.tv_sec * 1000000) + start.tv_usec;
	return (micros);
}
