/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:34:19 by dmelo-ca          #+#    #+#             */
/*   Updated: 2024/12/17 13:09:48 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
        if (!allocate_philos(&head))
        {
            printf("TODO LOGICA DE SAIDA!\n");
            return (-1);
        }
        thread_creator(&head);
        pause();
    }
    else
    {
        printf(RED "[PARSE]: Erro ao ler os argumentos!\n" RESET);
        return (1);
    }
        
    return (0);
}