/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 21:16:50 by davi              #+#    #+#             */
/*   Updated: 2025/02/26 09:39:28 by dmelo-ca         ###   ########.fr       */
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
	destroy_mutexes(head);
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

void	free_forks(t_head *head)
{
	int	i;

	i = 0;
	while (i < head->init.philo_amount)
	{
		pthread_mutex_destroy(&head->forks[i]);
		i++;
	}
	free(head->forks);
	pthread_mutex_destroy(&head->print);
	pthread_mutex_destroy(&head->write);
	pthread_mutex_destroy(&head->end_block);
}

void	free_philos(t_head *head)
{
	free_forks(head);
	free(head->phil_arr);
}
