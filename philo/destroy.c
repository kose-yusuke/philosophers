/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoseki <ykoseki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:15:00 by koseki.yusu       #+#    #+#             */
/*   Updated: 2024/07/30 21:46:13 by ykoseki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy(t_philo *philo)
{
	int	i;

	i = 0;
	while (philo->args->num_of_philos > i)
	{
		pthread_mutex_destroy(philo[i].right_fork);
		pthread_mutex_destroy(philo[i].left_fork);
		i++;
	}
	pthread_mutex_destroy(&philo->args->eat_lock);
	pthread_mutex_destroy(&philo->args->dead_lock);
	pthread_mutex_destroy(&philo->args->printf_lock);
}
