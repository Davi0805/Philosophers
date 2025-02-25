/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi <davi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:26:35 by dmelo-ca          #+#    #+#             */
/*   Updated: 2025/02/24 21:51:18 by davi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo)
{
	if (philo->philo_id % 2 == 0) // left first
	{
		pthread_mutex_lock(philo->l_fork);
		ft_log(FORK, philo);
		pthread_mutex_lock(philo->r_fork);
		ft_log(FORK, philo);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		ft_log(FORK, philo);
		pthread_mutex_lock(philo->l_fork);
		ft_log(FORK, philo);
	}
}

void	eating(t_philo *philo)
{
	t_head	*head;

	head = philo->head;
	if (get_int(&head->end_block, &head->end_flag))
		return ;
	take_fork(philo);
	set_int(&philo->eat, &philo->last_meal, get_time(&head->start, &head->end));
	ft_log(EAT, philo);
	if (head->init.eat_amount != -1)
		philo->meals++;
	custom_sleep(head->init.time_eat, head);
	/* usleep(head->init.time_eat); */
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	sleeping(t_philo *philo)
{
	t_head	*head;

	head = philo->head;
	ft_log(SLEEP, philo);
	/* usleep(head->init.time_to_sleep); */
	custom_sleep(head->init.time_to_sleep, head);
}

void	thinking(t_philo *philo)
{
	ft_log(THINK, philo);
	usleep(500);
}

void	philo_full(t_philo *philo)
{
	t_head	*head;

	head = philo->head;
	set_int(&philo->eat, &philo->full, 1);
	increment(&head->write, &head->full_amount);
}
