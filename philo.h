/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:41:35 by dmelo-ca          #+#    #+#             */
/*   Updated: 2024/12/18 16:15:34 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>

#define RESET "\033[0m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"

typedef struct s_philo t_philo;

typedef struct s_init
{
    int philo_amount;
    int philo_created;
    int time_die;
    int time_eat;
    int time_to_sleep;
    int eat_amount;
}               t_init;

typedef struct s_head
{
    t_init  init;
    int     someone_died;
    struct timeval start;
    struct timeval end;
    pthread_mutex_t    *forks;
    t_philo       *phil_arr;
    int           threadsync;
    pthread_mutex_t     print;
    pthread_mutex_t     write;
    pthread_t           monitor;
}               t_head;

typedef struct s_philo
{
    int         philo_id;
    pthread_t thread;
    int     meals;
    int     ate;
    t_head  *head;
    pthread_mutex_t *l_fork;
    pthread_mutex_t *r_fork;
}               t_philo;

//Init
void    init_time(t_head *head);
void    init_head(t_head *head, int ac, char **av);
int	parse_error(int ac, char **av);


//AUX
long	ft_atol(const char *str);
int     ft_isdigit(int c);

//THREAD FUNCS
long  get_time(struct timeval *start, struct timeval *end);
int		allocate_forks(t_head *head);
int	allocate_philos(t_head *head);
int thread_creator(t_head *head);
void    *monitor_func(void *arg);
int thread_join(t_head *head);
void    *philo_func(void *arg);
void    take_fork(int id, t_head *head);
void    eating(int id, t_head *head);
void    sleeping(int id, t_head *head);
void    thinking(int id, t_head *head);
/* void	allocate_threads(pthread_t **threads, t_head *head); */

#endif