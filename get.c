/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi <davi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:11:41 by davi              #+#    #+#             */
/*   Updated: 2024/12/19 14:15:17 by davi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int     someone_died(int bool, t_head *head)
{
    int i;
    pthread_mutex_lock(&head->write);
    i = bool;
    pthread_mutex_unlock(&head->write);
    return (i);
}