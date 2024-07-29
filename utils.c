/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koseki.yusuke <koseki.yusuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:30:26 by koseki.yusu       #+#    #+#             */
/*   Updated: 2024/07/29 12:24:38 by koseki.yusu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_overflow(long long num, int onedigit, int type)
{
	if (type == 1 && ((num > LLONG_MAX / 10) || (num == LLONG_MAX / 10
				&& onedigit > 7)))
		return (-1);
	if (type == -1 && ((-1 * num < LLONG_MIN / 10) || (-1 * num == LLONG_MIN
				/ 10 && onedigit > 8)))
		return (0);
	return (1);
}

long	ft_atoi(const char *str)
{
	int			type;
	long long	num;
	int			overflow;

	type = 1;
	num = 0;
	while (*str != '\0' && (*str == ' ' || *str == '\f' || *str == '\n'
			|| *str == '\r' || *str == '\t' || *str == '\v'))
		str++;
	if (*str != '\0' && (*str == '+' || *str == '-'))
	{
		if (*str == '-')
			type *= -1;
		str++;
	}
	while (*str != '\0' && *str >= '0' && *str <= '9')
	{
		overflow = check_overflow(num, *str - '0', type);
		if (overflow == -1 || overflow == 0)
			return (overflow);
		num = num * 10 + (*str - '0');
		str++;
	}
	return (type * num);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}