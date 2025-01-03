/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi <davi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:11:41 by davi              #+#    #+#             */
/*   Updated: 2024/12/19 14:15:17 by davi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Getter: Return the int received
// Using Mutex (&head->write)
int     someone_died(int bool, t_head *head)
{
    int i;
    pthread_mutex_lock(&head->write);
    i = bool;
    pthread_mutex_unlock(&head->write);
    return (i);
}

// Getter: Return the time passed in milisseconds
long  get_time(struct timeval *start, struct timeval *end)
{
    struct timeval result;
    long milisseconds;
    
    gettimeofday(end, NULL);
    result.tv_sec = end->tv_sec - start->tv_sec;
    result.tv_usec = end->tv_usec - start->tv_usec;
    milisseconds = result.tv_sec * 1000 + result.tv_usec / 1000;
    /* printf(GREEN "[Miliseconds]:" RESET " %ld\n", milisseconds); */
    return (milisseconds);
}