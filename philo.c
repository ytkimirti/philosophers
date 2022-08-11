#include "vars.h"
#include <pthread.h>
#include <time.h>
#include "unistd.h"
#include <stdio.h>

void	*philo_loop(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;


	usleep(1000);

	pthread_mutex_lock(&p->vars->writing_lock);

	printf("Hello! I am Philo %d\n", p->id);

	pthread_mutex_unlock(&p->vars->writing_lock);

	return (NULL);
}
