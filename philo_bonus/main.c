#include <stdio.h>
#include "philo.h"
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"
#include "vars.h"
#include "errors.h"
#include "init.h"

// Args are: 
// number_of_philosophers
// time_to_die
// time_to_eat
// time_to_sleep
// [number_of_times_each_philosopher_must_eat]
bool	parse_args(t_vars *vars, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (exit_program("Argument count does not match\n"
				"./philo time_to_die time_to_eat "
				"time_to_sleep [must_eat_count]"));
	vars->count = ft_atoi(argv[1]);
	vars->starve_time = ft_atoi(argv[2]);
	vars->eat_time = ft_atoi(argv[3]);
	vars->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
	{
		vars->is_infinite = false;
		vars->max_eat_count = ft_atoi(argv[5]);
	}
	else
	{
		vars->is_infinite = true;
		vars->max_eat_count = 0;
	}
	if (vars->count < 2 || vars->starve_time < 0 || vars->eat_time < 0
		|| vars->sleep_time < 0)
		return (exit_program("All values should be positive and "
				"There must be at least 2 philosophers."));
	return (true);
}

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

int	main(int argc, char *argv[])
{
	t_vars	vars;

	if (!parse_args(&vars, argc, argv))
		return (1);
	if (!init_philosophers(&vars))
		return (1);
	if (!init_mutexes(&vars))
		return (1);
	if (!init_threads(&vars))
		return (1);
	check_for_death(&vars);
	join_threads(&vars);
	destroy_mutexes(&vars);
	return (0);
}
