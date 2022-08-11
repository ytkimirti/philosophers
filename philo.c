#include "vars.h"
#include "colors.h"
#include <pthread.h>
#include <time.h>
#include "unistd.h"
#include <stdio.h>
#include "utils.h"

// No need to terminate with newline
void	print_status(t_philo	*philo, char *msg)
{
	if (philo->vars->stop)
		return;
	pthread_mutex_lock(&philo->vars->writing_lock);
	if (!philo->vars->stop)
		printf("%lld %d %s\n", get_time() - philo->vars->start_time, philo->id, msg);
	pthread_mutex_unlock(&philo->vars->writing_lock);
}

// NOTES:
// Fork 0 is at the right of philo one.
// Philo id's start from 1
// The fork at the right of philo 1 is fork 0
// So right fork is (id - 1) % count
// Left fork is (id - 2) % count
void	*philo_loop(void *arg)
{
	t_philo	*p;
	int			eat_count;

	p = (t_philo *)arg;
	eat_count = 0;
	if (p->id % 2 == 0)
		usleep(1000 * (p->vars->eat_time / 2));
	while (!p->vars->stop)
	{
		pthread_mutex_lock(&p->vars->forks[(p->id - 1) % p->vars->count]);
		pthread_mutex_lock(&p->vars->forks[(p->id - 2) % p->vars->count]);
		p->last_eat_time = get_time();
		print_status(p, "has taken a fork");
		usleep(1000 * p->vars->eat_time);
		eat_count++;
		pthread_mutex_unlock(&p->vars->forks[(p->id - 1) % p->vars->count]);
		pthread_mutex_unlock(&p->vars->forks[(p->id - 2) % p->vars->count]);
		if (!p->vars->is_infinite && eat_count >= p->vars->max_eat_count)
		{
			p->is_done = true;
			return (NULL);
		}
		print_status(p, "is sleeping");
		usleep(1000 * p->vars->sleep_time);
		print_status(p, "is thinking");
	}

	return (NULL);
}
