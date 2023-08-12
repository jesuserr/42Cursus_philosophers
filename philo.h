/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:55:36 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/12 15:43:54 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              DEFINES
*/
# define BLUE       "\033[0;94m"
# define RED        "\033[0;31m"
# define WHITE      "\033[0;37m"

# define ERROR_ARGS				0
# define ERROR_FORMAT			1
# define ERROR_PHILO			2
# define ERROR_TIMES			3
# define ERROR_MEALS			4
# define ERROR_MEM				5

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              HEADERS
*/
# include <unistd.h>    // for write
# include <stdlib.h>    // for malloc
# include <limits.h>	// for INT_MAX && INT_MIN
# include <stddef.h>	// for NULL
# include <stdio.h>		// for printf
# include <pthread.h>	// for threads
# include <sys/time.h>  // for timer

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              STRUCT DECLARATIONS
*/
struct	s_philo;

typedef struct s_info
{
	int				nbr_philos;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				max_meals;
	pthread_mutex_t	*forks_mtx;
	pthread_mutex_t	print_mtx;
	struct s_philo	*philo_list;
}				t_info;

typedef struct s_philo
{
	int		philo_id;
	int		meals;
	long	last_meal;
}				t_philo;

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              FUNCTION PROTOTYPES
*/
int		ft_error_handler(int error);
int		check_args(int argc, char **argv);

long	ft_atoi(const char *str);
int		ft_is_digit(char c);

long	get_time_ms(void);
long	get_time_us(void);
void	ft_usleep(long microsecs);
void	ft_msleep(long milisecs);

#endif