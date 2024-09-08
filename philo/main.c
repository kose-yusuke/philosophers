/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoseki <ykoseki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:28:12 by koseki.yusu       #+#    #+#             */
/*   Updated: 2024/07/30 21:50:38 by ykoseki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
// #include <libc.h>

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q philo");
// }

void	ft_parse_args(t_args *args, char **argv)
{
	args->num_of_philos = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		args->num_times_to_eat = ft_atoi(argv[5]);
	else
		args->num_times_to_eat = -1;
	args->start_time = get_current_time();
	args->dead_flag = 0;
	pthread_mutex_init(&args->eat_lock, NULL);
	pthread_mutex_init(&args->dead_lock, NULL);
	pthread_mutex_init(&args->printf_lock, NULL);
}

void	create_fork_array(pthread_mutex_t *forks, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->num_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_philo(t_philo *philo, t_args *args, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (args->num_of_philos > i)
	{
		philo[i].id = i;
		philo[i].args = args;
		philo[i].eating = 0;
		philo[i].eat_count = 0;
		philo[i].last_eat_time = args->start_time;
		philo[i].right_fork = &forks[i];
		if (i == args->num_of_philos - 1)
			philo[i].left_fork = &forks[0];
		else
			philo[i].left_fork = &forks[i + 1];
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_args			args;
	t_philo			*philo;
	pthread_mutex_t	*forks;

	if (!arg_check(argc, argv) || !arg_check2(argv))
		return (0);
	ft_parse_args(&args, argv);
	philo = (t_philo *)malloc(sizeof(t_philo) * args.num_of_philos);
	if (!philo)
		return (0);
	forks = malloc(sizeof(pthread_mutex_t) * args.num_of_philos);
	if (!forks)
	{
		free(philo);
		return (0);
	}
	create_fork_array(forks, &args);
	init_philo(philo, &args, forks);
	ft_thread_create(philo);
	ft_destroy(philo);
	free(forks);
	free(philo);
	return (0);
}
