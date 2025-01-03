/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:19:07 by dmelo-ca          #+#    #+#             */
/*   Updated: 2024/12/20 15:53:24 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *philo_func(void *arg)
{
    t_philo philo;

    philo = *((t_philo*)arg);
    while(philo.head->threadsync == 0)
    {
        pthread_mutex_lock(&philo.head->write);
        pthread_mutex_unlock(&philo.head->write);
    }
    if (philo.philo_id % 2 == 0)
        custom_sleep(30000, philo.head);
        /* usleep(30000); */
    while (someone_died(philo.head->someone_died, philo.head) == 0 && philo.meals != philo.head->init.eat_amount)
    {   
        if (philo.philo_id % 2 == 0)
        {
            pthread_mutex_lock(philo.l_fork);
                if (someone_died(philo.head->someone_died, philo.head))
                    break;
                take_fork(philo.philo_id, philo.head);
            pthread_mutex_lock(philo.r_fork);
                if (someone_died(philo.head->someone_died, philo.head))
                    break;
                take_fork(philo.philo_id, philo.head);
            philo.ate = 0;
                if (someone_died(philo.head->someone_died, philo.head))
                    break;
            eating(philo.philo_id, philo.head);
            philo.ate = 1;
            /* usleep(philo.head->init.time_eat); */
            custom_sleep(philo.head->init.time_eat, philo.head);
        }
        else
        {
            pthread_mutex_lock(philo.r_fork);
                if (someone_died(philo.head->someone_died, philo.head))
                    break;
                take_fork(philo.philo_id, philo.head);
            pthread_mutex_lock(philo.l_fork);
                if (someone_died(philo.head->someone_died, philo.head))
                    break;
                take_fork(philo.philo_id, philo.head);
            philo.ate = 0;
                if (someone_died(philo.head->someone_died, philo.head))
                    break;
            eating(philo.philo_id, philo.head);
            philo.ate = 1;
            /* usleep(philo.head->init.time_eat); */
            custom_sleep(philo.head->init.time_eat, philo.head);

        }
        pthread_mutex_unlock(philo.l_fork);
        pthread_mutex_unlock(philo.r_fork);
        if (someone_died(philo.head->someone_died, philo.head))
            break;
        sleeping(philo.philo_id, philo.head);
        /* usleep(philo.head->init.time_to_sleep); */
        custom_sleep(philo.head->init.time_to_sleep, philo.head);
        if (someone_died(philo.head->someone_died, philo.head))
            break;
        thinking(philo.philo_id, philo.head);
        philo.meals++;
    }
    if (philo.meals == philo.head->init.eat_amount)
    {
        pthread_mutex_lock(&philo.head->write);
        philo.head->full_amount += 1;
        pthread_mutex_unlock(&philo.head->write);
    }
    return (NULL);
}

void    *monitor_func(void *arg)
{
    t_head *head;
    int i;
    int comidos = 0;
    
    head = (t_head*)arg;
    while (head->threadsync == 0)
    {
        pthread_mutex_lock(&head->write);
        pthread_mutex_unlock(&head->write);
    }
    
    while(head->someone_died == 0 && head->full_amount != head->init.philo_amount)
    {
        usleep(head->init.time_die);
        i = -1;
        while (++i < head->init.philo_amount)
        {
            pthread_mutex_lock(&head->write);
            if (head->phil_arr[i].ate == 0 && comidos != 0)
                head->someone_died = 1;
            else
                comidos++;
            pthread_mutex_unlock(&head->write);
        }
        printf(RED "%lu ALGUEM MORREU ENT %d\n" RESET, get_time(&head->start, &head->end), head->someone_died);
    }
    return (NULL);
}