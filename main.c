/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:05:04 by codespace         #+#    #+#             */
/*   Updated: 2023/08/08 16:38:54 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_program(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	write(1, "hola\n", 5);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		ft_error_handler(ERROR_ARGS);
	detect_no_numbers_and_limits(argc, argv);
	init_program(argc, argv);
	return (0);
}
