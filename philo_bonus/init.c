#include "errors.h"
#include "init.h"
#include "philo.h"
#include "vars.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>
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
		vars->philos[i].is_done = false;
		vars->philos[i].vars = vars;
		vars->philos[i].last_eat_time = get_time();
		i++;
	}
	return (true);
}

bool	init_semaphores(t_vars *vars)
{
	int	i;

	vars->sem_forks = sem_open("philosopher_forks", O_CREAT);
	vars->sem_writing = sem_open("philosopher_writing", O_CREAT);
	return (true);
}

bool	init_processes(t_vars *vars)
{
	int		i;
	int		pid;

	i = 0;
	vars->stop = false;
	while (i < vars->count)
	{
		pid = fork();
		if (pid == -1)
			return (exit_program("Creating thread failed"));
		else if (pid == 0)
			philo_loop();
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

void	join_processes(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->count)
	{
		pthread_join(vars->philos[i].thread, NULL);
		i++;
	}
}
