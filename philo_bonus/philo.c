/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykimirti <ykimirti@42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:39:35 by ykimirti          #+#    #+#             */
/*   Updated: 2022/09/14 16:06:41 by ykimirti         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "vars.h"
#include <time.h>
#include "unistd.h"
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include "semaphores.h"
#include "utils.h"
#include <pthread.h>
#include "philo_utils.h"

// This threads checks if the process
// starved or not, every 1ms.
// If it starves, this
// posts the semaphore sem_closing.
// When the parent process gets this, it
// kills every single child process.
void	*thread_func(t_state *state)
{
	t_time	time;
	bool	is_dead;

	is_dead = false;
	print_status(state->philo, "Thread is here!");
	while (true)
	{
		usleep(1000);
		time = get_time();
		sem_wait(state->sem);
		if (time - state->last_eat_time > state->philo->vars->starve_time)
		{
			is_dead = true;
			print_status(state->philo, "died");
		}
		else if (!state->philo->vars->is_infinite
			&& state->eat_count > state->philo->vars->max_eat_count)
		{
			is_dead = true;
		}
		sem_post(state->sem);
		if (is_dead)
		{
			sem_post(state->philo->vars->sem_closing);
			break ;
		}
	}
	return (NULL);
}

void	init_stuff(t_state *state, t_philo *p)
{
	state->philo = p;
	state->last_eat_time = get_time();
	state->sem = open_semaphore_with_id(SEM_STATE_READ,
			state->philo->id, 1);
}

void	philo_entry(t_philo *p)
{
	t_state			state;
	pthread_t		thread;

	init_stuff(&state, p);
	print_status(p, "Philo has awaken!");
	pthread_create(&thread, NULL, (void *(*)(void *))thread_func, (void *)&state);
	if (p->id % 2 == 0)
		usleep(1000 * (p->vars->eat_time / 2));
	while (true)
	{
		sem_wait(p->vars->sem_forks);
		print_status(p, "has taken a fork");
		sem_wait(p->vars->sem_forks);
		print_status(p, "has taken a fork");
		set_last_eat_time(&state, state.sem);
		wait_ms(p->vars->eat_time);
		sem_post(p->vars->sem_forks);
		sem_post(p->vars->sem_forks);
		increment_eat_count(&state, state.sem);
		print_status(p, "is sleeping");
		wait_ms(p->vars->sleep_time);
	}
	while (true)
		;
}
