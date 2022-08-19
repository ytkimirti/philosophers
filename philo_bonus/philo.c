#include "vars.h"
#include <time.h>
#include "unistd.h"
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include "utils.h"

typedef struct s_state
{
	bool	is_dead;
	time_t	last_eat_time;
}	t_state;

// No need to terminate with newline
void	print_status(t_philo	*philo, char *msg)
{
	sem_wait(philo->vars->sem_writing);
	if (!philo->vars->stop)
		printf("%lld %d %s\n", get_time(), philo->id, msg);
	sem_post(philo->vars->sem_writing);
}

void	wait_ms(t_state *state, int ms)
{
	t_time	start_time;

	start_time = get_time();
	while (!state->is_dead && get_time() - start_time < ms)
		usleep(30);
}

// The entry point for the philosopher processes
// NOTES:
// Fork 0 is at the right of philo one.
// Philo id's start from 1
// The fork at the right of philo 1 is fork 0
// So right fork is (id - 1) % count
// Left fork is (id - 2) % count
void	philo_entry(t_philo *p)
{
	t_state	state;

	state.last_eat_time = get_time();
	if (p->id % 2 == 0)
		usleep(1000 * (p->vars->eat_time / 2));
	wait_ms(&state, p->id * 300);
	print_status(p, "Hello!!");
	while (true)
		;
}
