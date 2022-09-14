/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykimirti <ykimirti@42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 18:15:03 by ykimirti          #+#    #+#             */
/*   Updated: 2022/09/14 18:15:50 by ykimirti         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

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
	int	i;

	vars->forks = malloc(sizeof(pthread_mutex_t) * vars->count);
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
	int			i;
	pthread_t	*thread;

	i = 0;
	vars->stop = false;
	while (i < vars->count)
	{
		thread = &vars->philos[i].thread;
		if (pthread_create(thread, NULL, philo_loop, &vars->philos[i]))
			return (exit_program("Creating thread failed"));
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

void	join_threads(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->count)
	{
		pthread_join(vars->philos[i].thread, NULL);
		i++;
	}
}
