/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi <davi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:11:41 by davi              #+#    #+#             */
/*   Updated: 2025/02/24 21:54:11 by davi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Getter: Return the int received
// Using Mutex (&head->write)
int	someone_died(int bool, t_head *head)
{
	int	i;

	pthread_mutex_lock(&head->write);
	i = bool;
	pthread_mutex_unlock(&head->write);
	return (i);
}

// Getter: Return the time passed in milisseconds
long	get_time(struct timeval *start, struct timeval *end)
{
	struct timeval	result;
	long			milisseconds;

	gettimeofday(end, NULL);
	result.tv_sec = end->tv_sec - start->tv_sec;
	result.tv_usec = end->tv_usec - start->tv_usec;
	milisseconds = result.tv_sec * 1000 + result.tv_usec / 1000;
	return (milisseconds);
}

void	set_int(pthread_mutex_t *mutex, int *target, int value)
{
	pthread_mutex_lock(mutex);
	*target = value;
	pthread_mutex_unlock(mutex);
	return ;
}

int	get_int(pthread_mutex_t *mutex, int *value)
{
	int	temp;

	pthread_mutex_lock(mutex);
	temp = *value;
	pthread_mutex_unlock(mutex);
	return (temp);
}

void	increment(pthread_mutex_t *mutex, int *value)
{
	pthread_mutex_lock(mutex);
	(*value)++;
	pthread_mutex_unlock(mutex);
}
