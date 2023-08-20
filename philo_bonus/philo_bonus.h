/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 21:49:21 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/20 21:49:38 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

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
# define ERROR_TH				6

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
	int				total_meals;
	long			start_time;
	int				dead;
	int				active_threads;
	pthread_mutex_t	*forks_mtx;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	start_mtx;
	pthread_mutex_t	meals_mtx;
	struct s_philo	*philos_array;
	pthread_t		*philos_th;
	pthread_t		monitor;
}				t_info;

typedef struct s_philo
{
	int				philo_id;
	int				meals;
	long			last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_info	*info;
}				t_philo;

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              FUNCTION PROTOTYPES
*/
/*		errors.c		*/
int		ft_error_handler(int error, t_info *info);
int		check_args(int argc, char **argv);
/*		inits.c			*/
void	init_info(int argc, char **argv, t_info *info);
int		init_mutexes(t_info *info);
int		init_philos(t_info *info);
int		init_threads(t_info *info);
/*		main.c			*/
void	join_threads(t_info *info);
void	destroy_mutexes(t_info *info);
void	free_memory(t_info *info);
/*		monitor.c		*/
void	*monitoring(void *arg);
/*		routine.c		*/
void	*routine(void *arg);
/*		utils.c			*/
long	ft_atoi(const char *str);
int		ft_is_digit(char c);
long	get_time_ms(void);
void	ft_msleep(long milisecs);

#endif