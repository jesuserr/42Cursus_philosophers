/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 21:52:13 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/20 21:52:28 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str [i] == ' ' || (str [i] >= '\t' && str [i] <= '\r'))
		i++;
	if (str [i] == '-')
	{
		sign = -sign;
		i++;
	}
	else if (str [i] == '+')
		i++;
	while (str [i] >= '0' && str [i] <= '9')
	{
		result = (result * 10) + str [i] - '0';
		i++;
	}
	return (result * sign);
}

int	ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long	get_time_ms(void)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	return ((start.tv_sec * 1000) + (start.tv_usec / 1000));
}

void	ft_msleep(long milisecs)
{
	long	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < milisecs)
		usleep(milisecs / 100);
}
