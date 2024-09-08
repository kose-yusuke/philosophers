/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoseki <ykoseki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 21:29:59 by koseki.yusu       #+#    #+#             */
/*   Updated: 2024/07/30 21:50:34 by ykoseki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	dead_checker(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->eat_lock);
	if (get_current_time() - philo->last_eat_time > philo->args->time_to_die)
	{
		pthread_mutex_unlock(&philo->args->eat_lock);
		died(philo);
		pthread_mutex_lock(&philo->args->dead_lock);
		philo->args->dead_flag = 1;
		pthread_mutex_unlock(&philo->args->dead_lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->args->eat_lock);
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
		pthread_mutex_lock(&philo->args->eat_lock);
		if (philo[i].eat_count >= philo->args->num_times_to_eat)
			full++;
		pthread_mutex_unlock(&philo->args->eat_lock);
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
