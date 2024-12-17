/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:26:35 by dmelo-ca          #+#    #+#             */
/*   Updated: 2024/12/17 16:52:26 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    take_fork(int id, t_head *head)
{
    pthread_mutex_lock(&head->print);
    gettimeofday(&head->end, NULL);
    printf("%d has taken the fork\n", id);
    pthread_mutex_unlock(&head->print);
}

void    eating(int id, t_head *head)
{
    pthread_mutex_lock(&head->print);
    gettimeofday(&head->end, NULL);
    printf("%d is eating\n", id);
    pthread_mutex_unlock(&head->print);
}

void    sleeping(int id, t_head *head)
{
    pthread_mutex_lock(&head->print);
    gettimeofday(&head->end, NULL);
    printf("%d is sleeping\n", id);
    pthread_mutex_unlock(&head->print);
}

void    thinking(int id, t_head *head)
{
    pthread_mutex_lock(&head->print);
    gettimeofday(&head->end, NULL);
    printf("%d is thinking\n", id);
    pthread_mutex_unlock(&head->print);
}