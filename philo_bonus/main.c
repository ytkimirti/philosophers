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

// There N forks in the middle of the table
// Processes need to know these:
// - Their ID
// - Forks semaphore
// - Writing semaphore
// - The timing values
int	main(int argc, char *argv[])
{
	t_vars	vars;

	if (!parse_args(&vars, argc, argv))
		return (1);
	if (!init_philosophers(&vars))
		return (1);
	if (!init_semaphores(&vars))
		return (1);
	if (!init_processes(&vars))
		return (1);
	check_for_death(&vars);
	join_threads(&vars);
	destroy_mutexes(&vars);
	return (0);
}
