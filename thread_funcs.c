/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:19:07 by dmelo-ca          #+#    #+#             */
/*   Updated: 2025/02/25 17:09:08 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_func(void *arg)
{
	t_philo	*philo;
	t_head	*head;

	philo = (t_philo *)arg;
	head = philo->head;
	thread_sync(philo->head);
	if (philo->philo_id % 2 == 0)
		usleep(3000);
	while (!get_int(&head->end_block, &head->end_flag))
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
		if (head->init.eat_amount != -1 && get_int(&head->write, &head->full_amount) == head->init.philo_amount)
		{
			set_int(&head->end_block, &head->end_flag, 1);
			break ;
		}
		current_time = get_time(&head->start, &head->end);
		if (get_int(&philo_arr[i].eat, &philo_arr[i].full) == 0 && current_time
			- get_int(&philo_arr[i].mutex, &philo_arr[i].last_meal) >= head->init.time_die / 1000)
		{
			ft_log(DIE, &philo_arr[i]);
			set_int(&head->end_block, &head->end_flag, 1);
		}
		i = (i + 1) % head->init.philo_amount;
	}
	return (NULL);
}
