#include "errors.h"
#include "init.h"
#include "philo.h"
#include "vars.h"
#include <stdio.h>
#include <stdlib.h>
#include "colors.h"
#include "utils.h"

bool	init_philosophers(t_vars *vars)
{
	int		i;

	vars->philos = (t_philo *)malloc(sizeof(t_philo) * vars->count);
	if (!vars->philos)
		return (exit_program("malloc failed!"));
	i = 0;
	while (i < vars->count)
	{
		vars->philos[i].id = i + 1;
		vars->philos[i].thread = NULL;
		vars->philos[i].is_done = false;
		vars->philos[i].vars = vars;
		vars->philos[i].last_eat_time = get_time();
		i++;
	}
	return (true);
}

bool	init_mutexes(t_vars *vars)
{
	int i;

	vars->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * vars->count);
	if (!vars->forks)
		return (exit_program("malloc failed!"));
	i = 0;
	while (i < vars->count)
	{
		if (pthread_mutex_init(&(vars->forks[i]), NULL))
			return (false);
		i++;
	}
	if (pthread_mutex_init(&(vars->writing_lock), NULL))
		return (false);
	return (true);
}

bool	init_threads(t_vars *vars)
{
	int	i;

	printf(YEL "Creating threads...\n" RST);
	i = 0;
	vars->stop = false;

	while (i < vars->count)
	{
		if (pthread_create(&(vars->philos[i].thread), NULL, philo_loop, (void *)(&vars->philos[i])) != 0)
			return (exit_program("Creating thread failed"));
		printf(YEL "Thread for philo %d created!\n" RST, vars->philos[i].id);
		i++;
	}
	return (true);
}

void	destroy_mutexes(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->count)
	{
		pthread_mutex_destroy(&(vars->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(vars->writing_lock));
}

void join_threads(t_vars *vars)
{
	int	i;

	printf(YEL "Joining threads...\n" RST);
	i = 0;
	while (i < vars->count)
	{
		pthread_join(vars->philos[i].thread, NULL);
		printf(YEL "Joined thread %d\n" RST, vars->philos[i].id);
		i++;
	}
}
