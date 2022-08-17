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

bool	check_is_all_done(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->count)
	{
		if (!vars->philos[i].is_done)
			return (false);
		i++;
	}
	return (true);
}

void	check_for_death(t_vars *vars)
{
	int		i;
	t_time	diff;

	while (true)
	{
		usleep(50);
		i = 0;
		while (i < vars->count)
		{
			diff = get_time() - vars->philos[i].last_eat_time;
			if (!vars->philos->is_done && diff > vars->starve_time)
			{
				print_status(&vars->philos[i], "died");
				vars->stop = true;
				return ;
			}
			i++;
		}
		if (check_is_all_done(vars))
		{
			vars->stop = true;
			return ;
		}
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

	if (!parse_args(&vars, argc, argv))
		return (1);
	if (!init_philosophers(&vars))
		return (1);
	if (!init_mutexes(&vars))
		return (1);
	if (!init_processes(&vars))
		return (1);
	check_for_death(&vars);
	join_threads(&vars);
	destroy_mutexes(&vars);
	return (0);
}
