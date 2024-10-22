/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 21:49:21 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/26 23:42:12 by jesuserr         ###   ########.fr       */
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
# define ERROR_SEM				7
# define ERROR_PID				8
# define MAX_PHILOS				200
# define MIN_TIME				60

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              HEADERS
*/
# include <unistd.h>    // for usleep
# include <stdlib.h>    // for malloc & free
# include <limits.h>	// for INT_MAX && INT_MIN
# include <stddef.h>	// for NULL
# include <stdio.h>		// for printf
# include <pthread.h>	// for threads
# include <sys/time.h>  // for timer
# include <semaphore.h>	// for semaphores
# include <sys/stat.h>	// for sem_open modes
# include <fcntl.h>		// for sem_open modes
# include <signal.h>	// for kill

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              STRUCT DECLARATIONS
*/
typedef struct s_info
{
	int				nbr_philos;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				max_meals;
	long			start_time;	
	sem_t			*forks_sem;
	sem_t			*print_sem;
	sem_t			*dead_sem;
	sem_t			*meals_sem;
	pid_t			*pid_philos;
	pthread_t		meals_monitor;
	pthread_t		pid_monitor;
	int				philo_id;
	int				meals;
	long			last_meal;
}				t_info;

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              FUNCTION PROTOTYPES
*/
/*		errors_bonus.c		*/
int		ft_error_handler(int error, t_info *info);
int		ft_error_handler_sem(int error, t_info *info);
int		check_args(int argc, char **argv);
/*		inits_bonus.c		*/
int		init_info(int argc, char **argv, t_info *info);
int		init_semaphores(t_info *info);
int		init_meals_monitor(t_info *info);
int		init_processes(t_info *info);
/*		main_bonus.c		*/
void	close_semaphores(t_info *info);
void	kill_processes(t_info *info);
/*		monitor_bonus.c		*/
void	*nbr_meals_monitor(void *arg);
void	*pid_monitor(void *arg);
/*		routine_bonus.c		*/
void	*routine(t_info *info);
/*		utils_bonus.c		*/
long	ft_atoi(const char *str);
int		ft_is_digit(char c);
long	get_time_ms(void);
void	ft_msleep(long milisecs);

#endif