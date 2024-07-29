/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koseki.yusuke <koseki.yusuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 21:29:59 by koseki.yusu       #+#    #+#             */
/*   Updated: 2024/07/29 12:24:46 by koseki.yusu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	dead_checker(t_philo *philo)
{
	if (get_current_time() - philo->last_eat_time > philo->args->time_to_die)
	{
		died(philo);
		pthread_mutex_lock(&philo->args->dead_lock);
		philo->args->dead_flag = 1;
		pthread_mutex_unlock(&philo->args->dead_lock);
		return (true);
	}
	return (false);
}

bool	all_eat_checker(t_philo *philo)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	if (philo->args->num_times_to_eat == -1)
		return (false);
	while (i < philo->args->num_of_philos)
	{
		pthread_mutex_lock(&philo->args->all_eat_lock);
		if (philo[i].eat_count >= philo->args->num_times_to_eat)
			full++;
		pthread_mutex_unlock(&philo->args->all_eat_lock);
		i++;
	}
	if (full == philo->args->num_of_philos)
	{
		pthread_mutex_lock(&philo->args->dead_lock);
		philo->args->dead_flag = 1;
		pthread_mutex_unlock(&philo->args->dead_lock);
		return (true);
	}
	return (false);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)arg;
	while (!check_stop(philos))
	{
		i = 0;
		while (i < philos->args->num_of_philos)
		{
			if (dead_checker(&philos[i]) || all_eat_checker(philos))
			{
				return (NULL);
			}
			i++;
		}
		ft_usleep(1);
	}
	return (NULL);
}
