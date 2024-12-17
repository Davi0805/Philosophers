/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:34:43 by dmelo-ca          #+#    #+#             */
/*   Updated: 2024/12/17 16:32:42 by dmelo-ca         ###   ########.fr       */
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
void	init_philo(t_head *head, int i)
{
	if (!i) // Primeiro philo
	{
		head->phil_arr[i].philo_id = i + 1;
		head->phil_arr[i].eating = 0;
		head->phil_arr[i].meals = 0;
		head->phil_arr[i].head = head;
		pthread_mutex_init(&head->phil_arr[i].r_fork, NULL);
	}
	else if (i == head->init.philo_amount - 1) // Ultimo philo
	{
		head->phil_arr[i].philo_id = i + 1;
		head->phil_arr[i].eating = 0;
		head->phil_arr[i].meals = 0;
		head->phil_arr[i].head = head;
		pthread_mutex_init(&head->phil_arr[i].r_fork, NULL);
		head->phil_arr[i].l_fork = &head->phil_arr[head->init.philo_amount - 1].r_fork;
	}
	else // Outros
	{
		head->phil_arr[i].philo_id = i + 1;
		head->phil_arr[i].eating = 0;
		head->phil_arr[i].meals = 0;
		head->phil_arr[i].head = head;
		pthread_mutex_init(&head->phil_arr[i].r_fork, NULL);
		head->phil_arr[i].l_fork = &head->phil_arr[i - 1].r_fork;
	}
	head->phil_arr[0].l_fork = &head->phil_arr[head->init.philo_amount - 1].r_fork;
	pthread_mutex_init(head->phil_arr[0].l_fork, NULL);
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