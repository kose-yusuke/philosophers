/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koseki.yusuke <koseki.yusuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:28:12 by koseki.yusu       #+#    #+#             */
/*   Updated: 2024/07/29 12:32:10 by koseki.yusu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void print_init(t_philo *philo, t_args *args)
// {
//     printf("Arguments:\n");
//     printf("Number of philosophers: %d\n", args->num_of_philos);
//     printf("Time to die: %zu\n", args->time_to_die);
//     printf("Time to eat: %zu\n", args->time_to_eat);
//     printf("Time to sleep: %zu\n", args->time_to_sleep);
//     printf("Number of times to eat: %d\n", args->num_times_to_eat);

//     printf("\nPhilosophers:\n");
//     for (int i = 0; i < args->num_of_philos; i++)
//     {
//         printf("Philosopher %d:\n", philo[i].id);
//         printf("ID: %d\n", philo[i].id);
//         printf("Args pointer: %p\n", (void*)philo[i].args);
//         printf("Fork mutex pointer: %p\n", (void*)&philo[i].fork);
//     }
// }

#include <libc.h>

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q philo");
// }

int	check_digit(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] != '\0')
	{
		if (argv[i] < '0' || argv[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	arg_check(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("wrong argument number\n");
		return (0);
	}
	if (ft_atoi(argv[1]) > 200 || ft_atoi(argv[1]) < 1 || check_digit(argv[1]))
	{
		printf("wrong philosophers number\n");
		return (0);
	}
	if (ft_atoi(argv[2]) < 1 || check_digit(argv[2]))
	{
		printf("wrong time to die\n");
		return (0);
	}
	return (1);
}

int	arg_check2(char **argv)
{
	if (ft_atoi(argv[3]) < 1 || check_digit(argv[3]))
	{
		printf("wrong time to eat\n");
		return (0);
	}
	if (ft_atoi(argv[4]) < 1 || check_digit(argv[4]))
	{
		printf("wrong time to sleep\n");
		return (0);
	}
	if (argv[5] && (ft_atoi(argv[5]) < 1 || check_digit(argv[5])))
	{
		printf("wrong num_times_to_eat\n");
		return (0);
	}
	return (1);
}

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
	pthread_mutex_init(&args->stop_lock, NULL);
	pthread_mutex_init(&args->all_eat_lock, NULL);
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
