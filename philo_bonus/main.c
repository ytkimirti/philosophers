#include <stdio.h>
#include "philo.h"
#include <sys/semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"
#include "vars.h"
#include "errors.h"
#include "init.h"
#include "parse.h"
#include "semaphores.h"
#include <signal.h>

void	wait_for_death(t_vars *vars, int *pids)
{
	int i;

	usleep(1000 * 1000 * 2);
	i = 0;
	while (i < vars->count)
	{
		printf("%d\n", pids[i]);
		i++;
	}
}

void	kill_processes(t_vars *vars, int *pids)
{
	int	i;

	sem_wait(vars->sem_writing);
	i = 0;
	while (i < vars->count)
	{
		kill(pids[i], SIGTERM);
		i++;
	}
}

// There N forks in the middle of the table
// Processes need to know these:
// - Their ID
// - Forks semaphore
// - Writing semaphore
// - The timing values
int	main(int argc, char *argv[])
{
	t_vars	vars;
	int		*pids;

	parse_args(&vars, argc, argv);
	init_philosophers(&vars);
	init_semaphores(&vars);
	pids = init_processes(&vars);
	wait_for_death(&vars, pids);
	close_semaphores(&vars);
	return (0);
}
