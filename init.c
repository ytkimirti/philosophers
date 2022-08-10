#include "errors.h"
#include "philo.h"
#include "vars.h"
#include <stdlib.h>

bool	init_philosophers(t_vars *vars)
{
	int		i;

	vars->philos = (t_philo *)malloc(sizeof(t_philo) * vars->count);
	if (!vars->philos)
		return (false);
	i = 0;
	while (i < vars->count)
	{
		vars->philos[i].id = i + 1;
		vars->philos[i].thread = NULL;
		i++;
	}
	return (true);
}

bool	init_mutexes(t_vars *vars)
{
	int i;
	t_philo	*philo;

	i = 0;
	while (i < vars->count)
	{
		if (pthread_mutex_init(&(vars->forks[i]), NULL))
			return (false);
	}
	if (pthread_mutex_init(&(vars->writing_lock), NULL))
		return (false);
	return (true);
}

bool	init_threads(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->count)
	{
		if (!pthread_create(&(vars->philos[i].thread), NULL, philo_loop, (void *)vars))
			return (exit_program("Creating thread failed"));
		i++;
	}
	return (true);
}
