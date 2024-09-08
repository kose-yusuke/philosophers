/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoseki <ykoseki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:03:50 by ykoseki           #+#    #+#             */
/*   Updated: 2024/07/30 19:13:50 by ykoseki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	taken_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	printf_wrapper(philo, " has taken a fork\n");
	if (philo->args->num_of_philos == 1)
	{
		ft_usleep(philo->args->time_to_die);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	printf_wrapper(philo, " has taken a fork\n");
}

void	eat(t_philo *philo)
{
	philo->eating = 1;
	printf_wrapper(philo, " is eating\n");
	pthread_mutex_lock(&philo->args->eat_lock);
	philo->last_eat_time = get_current_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->args->eat_lock);
	ft_usleep(philo->args->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	printf_wrapper(philo, " is sleeping\n");
	ft_usleep(philo->args->time_to_sleep);
}

void	think(t_philo *philo)
{
	printf_wrapper(philo, " is thinking\n");
}

void	died(t_philo *philo)
{
	printf_wrapper(philo, " died\n");
}
