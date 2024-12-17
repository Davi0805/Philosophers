/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:19:07 by dmelo-ca          #+#    #+#             */
/*   Updated: 2024/12/17 17:08:58 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *philo_func(void *arg)
{
    t_philo philo;

    philo = *((t_philo*)arg);
    printf("philo %d iniciado\n", philo.philo_id);
    while(philo.head->threadsync == 0)
    {
        pthread_mutex_lock(&philo.head->write);
        printf("[THREAD SYNC]: %d\n", philo.head->threadsync);
        pthread_mutex_unlock(&philo.head->write);
    }
    if (philo.philo_id % 2 == 0)
        usleep(30000);
    while (1)
    {
        if (philo.philo_id % 2 == 0)
        {
            pthread_mutex_lock(philo.l_fork);
            take_fork(philo.philo_id, philo.head);
            pthread_mutex_lock(&philo.r_fork);
            take_fork(philo.philo_id, philo.head);
            eating(philo.philo_id, philo.head);
            usleep(300000);
            pthread_mutex_unlock(philo.l_fork);
            pthread_mutex_unlock(&philo.r_fork);
        }
        else
        {
            pthread_mutex_lock(&philo.r_fork);
            take_fork(philo.philo_id, philo.head);
            pthread_mutex_lock(philo.l_fork);
            take_fork(philo.philo_id, philo.head);
            eating(philo.philo_id, philo.head);
            usleep(300000);
            pthread_mutex_unlock(&philo.r_fork);
            pthread_mutex_unlock(philo.l_fork);
        }
        sleeping(philo.philo_id, philo.head);
        usleep(60000);
        thinking(philo.philo_id, philo.head);
        usleep(120000);
    }
    return (NULL);
}