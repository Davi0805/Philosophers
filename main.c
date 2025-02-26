/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:34:19 by dmelo-ca          #+#    #+#             */
/*   Updated: 2025/02/26 09:40:17 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_head	head;

	if ((ac == 5 || ac == 6) && parse_error(ac, av) == 0)
	{
		init_head(&head, ac, av);
		if (allocate_forks(&head) == -1)
		{
			free_forks(&head);
			return (1);
		}
		if (allocate_philos(&head) == -1)
		{
			free_philos(&head);
			return (1);
		}
		thread_creator(&head);
		thread_join(&head);
		free_resources(&head);
	}
	else
	{
		printf(RED "[PARSE]: Erro ao ler os argumentos!\n" RESET);
		return (1);
	}
	return (0);
}
