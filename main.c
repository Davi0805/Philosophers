/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:34:19 by dmelo-ca          #+#    #+#             */
/*   Updated: 2024/12/18 15:55:43 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    t_head head;
    /* pthread_t *threads; */

    
    /* threads = NULL; */
    if ((ac == 5 || ac == 6) && parse_error(ac, av) == 0)
    {
        printf(GREEN "[PARSE]:" RESET " SUCESSO!\n");
        init_head(&head, ac, av);
        init_time(&head);
        allocate_forks(&head);
        if (!allocate_philos(&head))
        {
            printf("TODO LOGICA DE SAIDA!\n");
            return (-1);
        }
        thread_creator(&head);
        thread_join(&head);
    }
    else
    {
        printf(RED "[PARSE]: Erro ao ler os argumentos!\n" RESET);
        return (1);
    }
        
    return (0);
}