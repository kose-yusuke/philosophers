/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koseki.yusuke <koseki.yusuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:15:00 by koseki.yusu       #+#    #+#             */
/*   Updated: 2024/07/29 12:24:30 by koseki.yusu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy(t_philo *philo)
{
	int i;

	i = 0;
	while (philo->args->num_of_philos > i)
	{
		// forkは一本一本mutex管理する感じか.
		pthread_mutex_destroy(philo[i].right_fork);
		pthread_mutex_destroy(philo[i].left_fork);
		i++;
	}
	pthread_mutex_destroy(&philo->args->eat_lock);
	pthread_mutex_destroy(&philo->args->dead_lock);
	pthread_mutex_destroy(&philo->args->stop_lock);
	pthread_mutex_destroy(&philo->args->all_eat_lock);
}