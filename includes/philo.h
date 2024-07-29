/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koseki.yusuke <koseki.yusuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:27:05 by koseki.yusu       #+#    #+#             */
/*   Updated: 2024/07/29 12:25:00 by koseki.yusu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_args
{
	int				num_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_times_to_eat;
	size_t			start_time;
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	all_eat_lock;
	pthread_mutex_t	printf_lock;
}					t_args;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				eating;
	int				eat_count;
	size_t			last_eat_time;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_args			*args;
}					t_philo;

long				ft_atoi(const char *str);
void				ft_thread_create(t_philo *philo);
void				*philos_routine(void *num);
void				ft_destroy(t_philo *philo);
size_t				get_current_time(void);
int					ft_usleep(size_t milliseconds);
void				*monitor_routine(void *arg);
void				died(t_philo *philo);
bool				check_stop(t_philo *philo);

#endif