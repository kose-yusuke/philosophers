/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoseki <ykoseki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 00:30:05 by koseki.yusu       #+#    #+#             */
/*   Updated: 2024/07/30 19:19:59 by ykoseki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_thread_create(t_philo *philo)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	while (philo->args->num_of_philos > i)
	{
		if (pthread_create(&philo[i].thread, NULL, &philos_routine, &philo[i]) \
			!= 0)
			ft_destroy(philo);
		i++;
	}
	if (pthread_create(&monitor, NULL, &monitor_routine, philo) != 0)
		ft_destroy(philo);
	i = 0;
	while (philo->args->num_of_philos > i)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			ft_destroy(philo);
		i++;
	}
	if (pthread_join(monitor, NULL) != 0)
		ft_destroy(philo);
}
