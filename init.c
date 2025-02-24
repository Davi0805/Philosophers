/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi <davi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:42:58 by dmelo-ca          #+#    #+#             */
/*   Updated: 2025/02/24 21:58:28 by davi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_error(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < ac)
	{
		if (ft_atol(av[i]) > 2147483647 || ft_atol(av[i]) < -2147483648)
			return (1);
		while (av[i][j] != '\0')
		{
			if (ft_isdigit(av[i][j]) == 0 && av[i][j] != '+')
				return (1);
			j++;
		}
		j = 0;
		i++;
	}
	if (ft_atol(av[1]) == 0 || ft_atol(av[1]) > 200
		|| ft_atol(av[2]) < 60 || ft_atol(av[3]) < 60 || ft_atol(av[4]) < 60)
	{
		return (1);
	}
	return (0);
}

// INIT: Inicia variaveis essenciais da struct head
void	init_head(t_head *head, int ac, char **av)
{
	head->init.philo_amount = (int)ft_atol(av[1]); //MEsma quantidade de forks
	head->init.time_die = (int)ft_atol(av[2]) * 1000;
	head->init.time_eat = (int)ft_atol(av[3]) * 1000;
	head->init.time_to_sleep = (int)ft_atol(av[4]) * 1000;
	head->someone_died = 0;
	head->full_amount = 0;
	head->end_flag = 0;
	pthread_mutex_init(&head->print, NULL);
	pthread_mutex_init(&head->write, NULL);
	pthread_mutex_init(&head->end_block, NULL);
	if (ac == 6)
		head->init.eat_amount = (int)ft_atol(av[5]);
	else
		head->init.eat_amount = -1; // Caso nao seja setado
	printf(GREEN "[VARIAVES INICIAIS]:" RESET " %d - %dmicros - %dmicros - %dmicros - %d \n",
		head->init.philo_amount, head->init.time_die, head->init.time_eat,
		head->init.time_to_sleep, head->init.eat_amount);
}

// INIT: Inicia a struct com o horario de inicio do programa
// Preenche (&head->start)
void	init_time(t_head *head)
{
	gettimeofday(&head->start, NULL);
}

// INIT: Inicia as threads dos philos e monitor
int	thread_creator(t_head *head)
{
	int	i;

	head->threadsync = 0;
	i = -1;
	while (++i < head->init.philo_amount)
	{
		pthread_create(&head->phil_arr[i].thread, NULL, philo_func, (void *)(&head->phil_arr[i]));
	}
	pthread_create(&head->monitor, NULL, monitor_func, (void *)head);
	pthread_mutex_lock(&head->write);
	init_time(head);
	head->threadsync = 1;
	pthread_mutex_unlock(&head->write);
	return (1);
}

// INIT?: Coleta os retornos das threads
int	thread_join(t_head *head)
{
	int	i;

	i = -1;
	while (++i < head->init.philo_amount)
		pthread_join(head->phil_arr[i].thread, NULL);
	pthread_join(head->monitor, NULL);
	printf(RED "[FIM] - PHILOS CHEIOS [%d] - QTD DE REFEICOES [%d]\n" RESET, head->full_amount, head->init.eat_amount);
	return (1);
}
