/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi <davi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 21:16:50 by davi              #+#    #+#             */
/*   Updated: 2025/02/24 21:54:58 by davi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_head *head)
{
	int	i;

	pthread_mutex_destroy(&head->print);
	pthread_mutex_destroy(&head->write);
	pthread_mutex_destroy(&head->end_block);
	i = 0;
	while (i < head->init.philo_amount)
	{
		pthread_mutex_destroy(&head->forks[i]);
		pthread_mutex_destroy(&head->phil_arr[i].eat);
		i++;
	}
}

void	free_resources(t_head *head)
{
	if (head->forks)
	{
		free(head->forks);
		head->forks = NULL;
	}
	if (head->phil_arr)
	{
		free(head->phil_arr);
		head->phil_arr = NULL;
	}
}
