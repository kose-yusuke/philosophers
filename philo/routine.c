/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoseki <ykoseki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:27:55 by koseki.yusu       #+#    #+#             */
/*   Updated: 2024/07/30 21:50:12 by ykoseki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
5 — 哲学者の数
800 — 哲学者が食べなければ死ぬ時間
200 — 哲学者が食事をするのにかかる時間
200 — 哲学者が眠るのにかかる時間
7 — プログラムを終了する前に哲学者全員が食事を摂る必要がある回数 **
*/

void	printf_wrapper(t_philo *philo, char *output)
{
	pthread_mutex_lock(&philo->args->dead_lock);
	if (philo->args->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo->args->dead_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->args->dead_lock);
	pthread_mutex_lock(&philo->args->printf_lock);
	printf("%zu%s%d%s", get_current_time() - philo->args->start_time, " ",
		philo->id, output);
	pthread_mutex_unlock(&philo->args->printf_lock);
}

bool	check_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->dead_lock);
	if (philo->args->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo->args->dead_lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->args->dead_lock);
	return (false);
}

void	*philos_routine(void *tmp)
{
	t_philo	*philo;

	philo = (t_philo *)tmp;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!check_stop(philo))
	{
		taken_fork(philo);
		if (philo->args->num_of_philos == 1)
			break ;
		eat(philo);
		sleeping(philo);
		think(philo);
	}
	return (NULL);
}
