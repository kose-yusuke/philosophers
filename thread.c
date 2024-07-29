/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koseki.yusuke <koseki.yusuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 00:30:05 by koseki.yusu       #+#    #+#             */
/*   Updated: 2024/07/29 12:24:34 by koseki.yusu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_thread_create(t_philo *philo)
{
	int i;
	pthread_t monitor;

	// if (pthread_create(&monitor, NULL, &monitor, program->philos) != 0)
	// 	destory_all("Thread creation error", program, forks);
	i = 0;
	// printf("%d\n",philo->args->num_of_philos);
	while (philo->args->num_of_philos > i)
	{
		pthread_create(&philo[i].thread, NULL, &philos_routine, &philo[i]);
		i++;
	}
	// monitorもスレッド立てる
	pthread_create(&monitor, NULL, &monitor_routine, philo);

	i = 0;
	while (philo->args->num_of_philos > i)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	// monitorもスレッドjoinする
	pthread_join(monitor, NULL);
}