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


void	init_philo(t_head *head, int i)
{
		head->phil_arr[i].philo_id = i + 1;
		head->phil_arr[i].meals = 0;
		head->phil_arr[i].head = head;
		head->phil_arr[i].ate = 0;
		head->phil_arr[i].l_fork = &head->forks[i];
		head->phil_arr[i].r_fork = &head->forks[(i + 1) % head->init.philo_amount];
}

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