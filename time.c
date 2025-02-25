/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:59:02 by dmelo-ca          #+#    #+#             */
/*   Updated: 2025/02/25 17:04:06 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	custom_sleep(long delay, t_head *head)
{
	long	time;

	time = get_time(&head->start, &head->end);
	while (get_time(&head->start, &head->end) - time < delay / 1000)
	{
		usleep(100);
	}
	return ;
}

// INIT: Inicia a struct com o horario de inicio do programa
// Preenche (&head->start)
void	init_time(t_head *head)
{
	gettimeofday(&head->start, NULL);
}
