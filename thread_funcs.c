/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:19:07 by dmelo-ca          #+#    #+#             */
/*   Updated: 2024/12/18 16:25:07 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *philo_func(void *arg)
{
    t_philo philo;

    philo = *((t_philo*)arg);
    /* printf("philo %d iniciado\n", philo.philo_id); */
    while(philo.head->threadsync == 0)
    {
        pthread_mutex_lock(&philo.head->write);
        pthread_mutex_unlock(&philo.head->write);
    }
    if (philo.philo_id % 2 == 0)
        usleep(30000);
    while (philo.head->someone_died == 0 && philo.meals != philo.head->init.eat_amount)
    {
        if (philo.philo_id % 2 == 0)
        {
            pthread_mutex_lock(philo.l_fork);
            take_fork(philo.philo_id, philo.head);
            pthread_mutex_lock(philo.r_fork);
            take_fork(philo.philo_id, philo.head);
            philo.ate = 0;
            eating(philo.philo_id, philo.head);
            philo.ate = 1;
            usleep(philo.head->init.time_eat);
        }
        else
        {
            pthread_mutex_lock(philo.r_fork);
            take_fork(philo.philo_id, philo.head);
            pthread_mutex_lock(philo.l_fork);
            take_fork(philo.philo_id, philo.head);
            philo.ate = 0;
            eating(philo.philo_id, philo.head);
            philo.ate = 1;
            usleep(philo.head->init.time_eat);

        }
        pthread_mutex_unlock(philo.l_fork);
        pthread_mutex_unlock(philo.r_fork);
        sleeping(philo.philo_id, philo.head);
        usleep(philo.head->init.time_to_sleep);
        thinking(philo.philo_id, philo.head);
        philo.meals++;
    }
    return (NULL);
}

// EXEMPLO SEM MUTEX, POREM NECESSITO IMPLEMENTAR
void    *monitor_func(void *arg)
{
    t_head *head;
    int i;
    
    head = (t_head*)arg;
    while(head->someone_died == 0)
    {
        usleep(head->init.time_die);
        i = -1;
        while (i < head->init.philo_amount)
        {
            if (head->phil_arr[i].ate == 0)
                head->someone_died = 1;
        }
    }
    return (NULL);
}