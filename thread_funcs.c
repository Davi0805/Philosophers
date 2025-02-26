/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:19:07 by dmelo-ca          #+#    #+#             */
/*   Updated: 2025/02/26 09:53:56 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->head->forks[0]);
	ft_log(FORK, philo);
	custom_sleep(philo->head->init.time_die, philo->head);
	ft_log(DIE, philo);
	set_int(&philo->head->end_block, &philo->head->end_flag, 1);
	pthread_mutex_unlock(&philo->head->forks[0]);
}

void	*philo_func(void *arg)
{
	t_philo	*philo;
	t_head	*head;

	philo = (t_philo *)arg;
	head = philo->head;
	thread_sync(philo->head);
	if (philo->philo_id % 2 == 0)
		usleep(3000);
	if (head->init.philo_amount == 1)
		one_philo(philo);
	while (!get_int(&head->end_block, &head->end_flag)
		&& head->init.philo_amount != 1)
	{
		if (head->init.eat_amount != -1 && philo->meals
			== head->init.eat_amount)
		{
			philo_full(philo);
			break ;
		}
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	*monitor_func(void *arg)
{
	t_head	*head;
	t_philo	*philo_arr;
	int		current_time;
	int		i;

	head = (t_head *)arg;
	philo_arr = head->phil_arr;
	thread_sync(head);
	i = 0;
	while (get_int(&head->end_block, &head->end_flag) == 0)
	{
		if (head->init.eat_amount != -1 && get_int(&head->write,
				&head->full_amount) == head->init.philo_amount)
		{
			set_int(&head->end_block, &head->end_flag, 1);
			break ;
		}
		current_time = get_time(&head->start, &head->end);
		is_dead(head, philo_arr, i, current_time);
		i = (i + 1) % head->init.philo_amount;
	}
	return (NULL);
}

void	is_dead(t_head *head, t_philo *philo_arr, int i, int current_time)
{
	if (get_int(&philo_arr[i].eat, &philo_arr[i].full) == 0 && current_time
		- get_int(&philo_arr[i].mutex, &philo_arr[i].last_meal)
		>= head->init.time_die / 1000)
	{
		ft_log(DIE, &philo_arr[i]);
		set_int(&head->end_block, &head->end_flag, 1);
	}
}
