/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:26:35 by dmelo-ca          #+#    #+#             */
/*   Updated: 2024/12/18 15:35:15 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    take_fork(int id, t_head *head)
{
    pthread_mutex_lock(&head->print);
    printf("%lu %d has taken a fork\n", get_time(&head->start, &head->end), id);
    pthread_mutex_unlock(&head->print);
}

void    eating(int id, t_head *head)
{
    pthread_mutex_lock(&head->print);
    printf("%lu %d is eating\n", get_time(&head->start, &head->end), id);
    pthread_mutex_unlock(&head->print);
}

void    sleeping(int id, t_head *head)
{
    pthread_mutex_lock(&head->print);
    printf("%lu %d is sleeping\n", get_time(&head->start, &head->end), id);
    pthread_mutex_unlock(&head->print);
}

void    thinking(int id, t_head *head)
{
    pthread_mutex_lock(&head->print);
    printf("%lu %d is thinking\n", get_time(&head->start, &head->end), id);
    pthread_mutex_unlock(&head->print);
}