/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykimirti <ykimirti@42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:39:35 by ykimirti          #+#    #+#             */
/*   Updated: 2022/09/12 11:48:03 by ykimirti         ###   ########.tr       */
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
void	*thread_func(void *arg)
{
	t_state	*state;
	t_time	time;

	state = (t_state *)arg;
	while (true)
	{
		usleep(1000);
		time = get_time();
		if (time - state->last_eat_time > state->philo->vars->starve_time)
		{
			print_status(state->philo, "died");
			sem_post(state->philo->vars->sem_closing);
			break ;
		}
		if (state->philo->vars->is_infinite
			&& state->eat_count > state->philo->vars->max_eat_count)
		{
			sem_post(state->philo->vars->sem_closing);
			break ;
		}
	}
	return (NULL);
}

void	init_state(t_state *state, t_philo *p)
{
	state->philo = p;
	state->last_eat_time = get_time();
	state->sem_state_read = open_semaphore_with_id(SEM_STATE_READ,
			state->philo->id, 1);
}

void	philo_entry(t_philo *p)
{
	t_state		state;
	pthread_t	thread;

	init_state(&state, p);
	pthread_create(&thread, NULL, thread_func, (void *)&state);
	if (p->id % 2 == 0)
		usleep(1000 * (p->vars->eat_time / 2));
	while (true)
	{
		sem_wait(p->vars->sem_forks);
		print_status(p, "has taken a fork");
		sem_wait(p->vars->sem_forks);
		print_status(p, "has taken a fork");
		set_last_eat_time(&state);
		wait_ms(p->vars->eat_time);
		sem_post(p->vars->sem_forks);
		sem_post(p->vars->sem_forks);
		state.eat_count++;
		print_status(p, "is sleeping");
		wait_ms(p->vars->sleep_time);
	}
	while (true)
		;
}
