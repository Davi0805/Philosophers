/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:34:43 by dmelo-ca          #+#    #+#             */
/*   Updated: 2025/02/25 17:07:18 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// INIT: Aloca o array de threads 
int	allocate_threads(pthread_t **threads, t_head *head)
{
	*threads = (pthread_t *)malloc(sizeof(pthread_t)
			*(head->init.philo_amount + 1));
	if (!*threads)
		return (-1);
	return (0);
}

// INIT: Aloca o array de philosophers e chama a funcao init_philo
// STRUCT: t_philo
int	allocate_philos(t_head *head)
{
	int	i;

	head->phil_arr = (t_philo *)malloc(sizeof(t_philo)
			* (head->init.philo_amount));
	if (!head->phil_arr)
		return (-1);
	i = -1;
	while (++i < head->init.philo_amount)
	{
		init_philo(head, i);
	}
	return (1);
}

// INIT: ALoca e inicia o array de forks
int	allocate_forks(t_head *head)
{
	int	i;

	head->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* (head->init.philo_amount));
	if (!head->forks)
		return (-1);
	i = -1;
	while (++i < head->init.philo_amount)
		pthread_mutex_init(&head->forks[i], NULL);
	return (1);
}

void	ft_log(int state, t_philo *philo)
{
	t_head	*head;

	head = philo->head;
	if (get_int(&head->end_block, &head->end_flag))
		return ;
	pthread_mutex_lock(&head->print);
	if (state == FORK)
		printf("%lu %d has taken a fork\n",
			get_time(&head->start, &head->end), philo->philo_id);
	else if (state == EAT)
		printf("%lu %d is eating\n",
			get_time(&head->start, &head->end), philo->philo_id);
	else if (state == SLEEP)
		printf("%lu %d is sleeping\n",
			get_time(&head->start, &head->end), philo->philo_id);
	else if (state == THINK)
		printf("%lu %d is thinking\n",
			get_time(&head->start, &head->end), philo->philo_id);
	else if (state == DIE)
		printf("%lu %d has died\n",
			get_time(&head->start, &head->end), philo->philo_id);
	pthread_mutex_unlock(&head->print);
}
