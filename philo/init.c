/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoseki <ykoseki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:01:47 by ykoseki           #+#    #+#             */
/*   Updated: 2024/07/30 19:02:16 by ykoseki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
