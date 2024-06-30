/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koseki.yusuke <koseki.yusuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:30:26 by koseki.yusu       #+#    #+#             */
/*   Updated: 2024/06/26 17:30:39 by koseki.yusu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t 	get_current_time ( void )
{ 
	struct  timeval 	time ; 

	if (gettimeofday(&time, NULL ) == -1 ) 
		write( 2 , "gettimeofday() error\n" , 22 ); 
	return (time.tv_sec * 1000 + time.tv_usec / 1000 ); 
}


int 	ft_usleep ( size_t milliseconds)
{ 
	size_t 	start; 

	start = get_current_time(); 
	while ((get_current_time() - start) < milliseconds) 
		usleep( 500 ); 
	return ( 0 ); 
}