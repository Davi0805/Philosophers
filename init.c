/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:42:58 by dmelo-ca          #+#    #+#             */
/*   Updated: 2024/12/18 16:19:57 by dmelo-ca         ###   ########.fr       */
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

void    init_head(t_head *head, int ac, char **av)
{
    head->init.philo_amount = (int)ft_atol(av[1]); //MEsma quantidade de forks
    head->init.time_die = (int)ft_atol(av[2]) * 1000;
    head->init.time_eat = (int)ft_atol(av[3]) * 1000;
    head->init.time_to_sleep = (int)ft_atol(av[4]) * 1000;
    head->init.philo_created = 1;
    head->someone_died = 0;
    pthread_mutex_init(&head->print, NULL);
    pthread_mutex_init(&head->write, NULL);
    if (ac == 6)
        head->init.eat_amount = (int)ft_atol(av[5]);
    else
        head->init.eat_amount = -1; // Caso nao seja setado
    printf(GREEN "[VARIAVES INICIAIS]:" RESET " %d - %dmicros - %dmicros - %dmicros - %d \n",
                    head->init.philo_amount, head->init.time_die, head->init.time_eat,
                    head->init.time_to_sleep, head->init.eat_amount);
}

void    init_time(t_head *head)
{
    gettimeofday(&head->start, NULL);
}

int thread_creator(t_head *head)
{
    int i;

    head->threadsync = 0;
    i = -1;
    while(++i < head->init.philo_amount)
    {
        pthread_create(&head->phil_arr[i].thread, NULL, philo_func, (void *)(&head->phil_arr[i]));
    }
    pthread_create(&head->monitor, NULL, monitor_func, (void *)&head);
    pthread_mutex_lock(&head->write);
    head->threadsync = 1;
    pthread_mutex_unlock(&head->write);
    return (1);
}

int thread_join(t_head *head)
{
    int i;

    i = -1;
    while(++i < head->init.philo_amount)
        pthread_join(head->phil_arr[i].thread, NULL);
    pthread_join(head->monitor, NULL);
    return (1);
}