/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:05:04 by codespace         #+#    #+#             */
/*   Updated: 2023/08/10 12:03:04 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine()
{
	printf("Hello from threads 1\n");
	usleep(8000);
	printf("Ending thread 1\n");
	return (NULL);
}

void	init_program(int argc, char **argv)
{
	pthread_t	p1;
	pthread_t	p2;

	(void)argc;
	(void)argv;
	pthread_create(&p1, NULL, &routine, NULL);
	pthread_create(&p2, NULL, &routine, NULL);
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
}

void	init_info(int argc, char **argv, t_data *info)
{
	info->nbr_philo = ft_atoi(argv[1]);
	info->die_time = ft_atoi(argv[2]);
	info->eat_time = ft_atoi(argv[3]);
	info->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		info->max_meals = ft_atoi(argv[5]);
	else
		info->max_meals = -1;
}

int	main(int argc, char **argv)
{
	t_data	info;

	if (argc < 5 || argc > 6)
		ft_error_handler(ERROR_ARGS);
	detect_no_numbers_and_limits(argc, argv);
	init_info(argc, argv, &info);
	printf("%d", info.max_meals);
	timer(0);
	init_program(argc, argv);
	timer(1);
	return (0);
}
