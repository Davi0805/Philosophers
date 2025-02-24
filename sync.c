#include "philo.h"

void	threadSync(t_head *head)
{
	while (get_int(&head->write, &head->threadsync) == 0)
		;
}