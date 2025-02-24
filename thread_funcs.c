/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi <davi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:19:07 by dmelo-ca          #+#    #+#             */
/*   Updated: 2025/02/24 21:48:35 by davi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_func(void *arg)
{
	t_philo	*philo;
	t_head	*head;

	philo = (t_philo *)arg;
	head = philo->head;
	threadSync(philo->head);
	if (philo->philo_id % 2 == 0)
		custom_sleep(30000, philo->head);
	while (!get_int(&head->end_block, &head->end_flag))
	{
		if (head->init.eat_amount != -1 && philo->meals == head->init.eat_amount)
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
	threadSync(head);
	i = 0;
	while (!get_int(&head->end_block, &head->end_flag))
	{
		if (head->init.eat_amount != -1 && get_int(&head->write, &head->full_amount) == head->init.philo_amount)
		{
			set_int(&head->end_block, &head->end_flag, 1);
			break ;
		}
		current_time = get_time(&head->start, &head->end);
		if (!get_int(&philo_arr[i].eat, &philo_arr[i].full) && current_time
			- get_int(&philo_arr[i].eat, &philo_arr[i].last_meal) >= head->init.time_die)
		{
			ft_log(DIE, &philo_arr[i]);
			set_int(&head->end_block, &head->end_flag, 1);
		}
		i = (i + 1) % head->init.philo_amount;
	}
	return (NULL);
}

/* void    *monitor_func(void *arg)
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
} */