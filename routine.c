/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koseki.yusuke <koseki.yusuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:27:55 by koseki.yusu       #+#    #+#             */
/*   Updated: 2024/07/29 12:25:52 by koseki.yusu      ###   ########.fr       */
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
	if (philo->args->dead_flag == 1)
		return ;
	pthread_mutex_lock(&philo->args->printf_lock);
	printf("%zu%s%d%s", get_current_time() - philo->args->start_time, " ",
		philo->id, output);
	pthread_mutex_unlock(&philo->args->printf_lock);
}

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

// 最後に食べた時間から, die_timeが経過したら, died関数を実行して即終了
// died(id, &philo[id]->start_time - get_current_time());

bool	check_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->stop_lock);
	if (philo->args->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo->args->stop_lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->args->stop_lock);
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
