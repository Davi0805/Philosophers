/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:34:43 by dmelo-ca          #+#    #+#             */
/*   Updated: 2024/12/18 16:12:22 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if ((c >= 48 && c <= 57))
	{
		return (1);
	}
	return (0);
}

long	ft_atol(const char *str)
{
	long	i;
	long	res;
	long	neg;

	i = 0;
	res = 0;
	neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' && str[i + 1] != '-')
		i++;
	if (str[i] == '-')
	{
		neg = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * neg);
}

// INIT: Aloca o array de threads 
int	allocate_threads(pthread_t **threads, t_head *head)
{
	*threads = (pthread_t *)malloc(sizeof(pthread_t) * (head->init.philo_amount + 1));
	if (!*threads)
		return (-1);
	return (0);
}
/* 
* @brief Iniciar variaveis dentro do array de philosophers
* @param t_head head e index i que sera utilizado no array
* @param int i que sera utilizado no array
*/

/*
f	[f1 f2 f3 f4 f5]
   
p    [p1		 p2 	p3 	p4	 p5]
	l=f1  r=1                   l=f5  r=f1
   l= f[n]  r=f[(n + 1) % no_philos ]
*/

// INIT: Inicia as variaveis dos philosophers
// STRUCT: t_philo
void	init_philo(t_head *head, int i)
{
		head->phil_arr[i].philo_id = i + 1;
		head->phil_arr[i].meals = 0;
		head->phil_arr[i].head = head;
		head->phil_arr[i].ate = 0;
		head->phil_arr[i].l_fork = &head->forks[i];
		head->phil_arr[i].r_fork = &head->forks[(i + 1) % head->init.philo_amount];
}

// INIT: Aloca o array de philosophers e chama a funcao init_philo
// STRUCT: t_philo
int	allocate_philos(t_head *head)
{
	int i;
	head->phil_arr = (t_philo *)malloc(sizeof(t_philo) * (head->init.philo_amount));
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
int		allocate_forks(t_head *head)
{
	int i;
	head->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (head->init.philo_amount));
	if (!head->forks)
		return (-1);
	i = -1;
	while (++i < head->init.philo_amount)
		pthread_mutex_init(&head->forks[i], NULL);
	return (1);
}

int	custom_sleep(int delay, t_head *head)
{
	int timebase;

	timebase = 0;
	while(timebase < delay && !someone_died(head->someone_died, head))
	{
		usleep(10);
		timebase += 10;
	}
	if (someone_died(head->someone_died, head))
		return (1);
	return (0);
}