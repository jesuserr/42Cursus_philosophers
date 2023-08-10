/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:22:18 by codespace         #+#    #+#             */
/*   Updated: 2023/08/10 11:23:35 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	timer(int action)
{
	static struct timeval	start;
	static struct timeval	end;
	long					secs_used;
	long					micros_used;

	if (action == 0)
		gettimeofday(&start, NULL);
	else if (action == 1)
	{
		gettimeofday(&end, NULL);
		secs_used = (end.tv_sec - start.tv_sec);
		micros_used = ((secs_used * 1000000) + end.tv_usec) - (start.tv_usec);
		printf ("Time: %d us\n", ((int)micros_used));
	}
}
