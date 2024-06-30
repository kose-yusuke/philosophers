/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koseki.yusuke <koseki.yusuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:28:12 by koseki.yusu       #+#    #+#             */
/*   Updated: 2024/06/30 15:45:32 by koseki.yusu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *count_to_100(void *arg)
{
 (void)arg;

 for(int i = 0; i < 100; i++)
    printf("The count has finished\n");
 return (NULL);
}

void *print_hello(void *arg)
{
 (void)arg;

 for(int i = 0; i < 100; i++)
  printf("Hello, world!\n");
 return (NULL);
}

int main()
{
 pthread_t thread_1;
 pthread_t thread_2;

    pthread_mutex_init(&a_lock, NULL ); 
    pthread_create(&thread_1, NULL, count_to_100, NULL);
    pthread_create(&thread_2, NULL, print_hello, NULL);
    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
}



// void error_massage(int i)
// {
//     if (i = -1)
//     {
//         printf("wrong argument number");
//         exit(1);
//     }
// }

// int arg_check(char **argv)
// {
    
// }

// int	main(int argc, char **argv)
// {
//     if ((argc != 5 && argv != 6) || !arg_check(argv))
//         error_massage(-1);
    
// }