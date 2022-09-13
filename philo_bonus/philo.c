/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykimirti <ykimirti@42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:39:35 by ykimirti          #+#    #+#             */
/*   Updated: 2022/09/13 20:12:17 by ykimirti         ###   ########.tr       */
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

typedef struct s_thread_arg
{
	t_state	*state;
	sem_t	*sem;
}	t_thread_arg;

// This threads checks if the process
// starved or not, every 1ms.
// If it starves, this
// posts the semaphore sem_closing.
// When the parent process gets this, it
// kills every single child process.
void	*thread_func(void *arg)
{
	sem_t	*sem;
	t_state	*state;
	t_time	time;
	bool	is_dead;

	state = ((t_thread_arg *)arg)->state;
	sem = ((t_thread_arg *)arg)->sem;
	is_dead = false;
	print_status(state->philo, "Thread is here!");
	while (true)
	{
		usleep(1000);
		time = get_time();
		sem_wait(sem);
		if (time - state->last_eat_time > state->philo->vars->starve_time)
		{
			is_dead = true;
			print_status(state->philo, "died");
		}
		else if (state->philo->vars->is_infinite
			&& state->eat_count > state->philo->vars->max_eat_count)
		{
			is_dead = true;
		}
		sem_post(sem);
		if (is_dead)
		{
			sem_post(state->philo->vars->sem_closing);
			break ;
		}
	}
	return (NULL);
}

void	init_stuff(t_state *state, t_philo *p, t_thread_arg *arg)
{
	state->philo = p;
	state->last_eat_time = get_time();
	arg->sem = open_semaphore_with_id(SEM_STATE_READ,
			state->philo->id, 1);
	arg->state = state;
}

void	philo_entry(t_philo *p)
{
	t_state			state;
	t_thread_arg	thread_arg;
	pthread_t		thread;

	init_stuff(&state, p, &thread_arg);
	print_status(p, "Philo has awaken!");
	pthread_create(&thread, NULL, thread_func, (void *)&thread_arg);
	// if (p->id % 2 == 0)
	// 	usleep(1000 * (p->vars->eat_time / 2));
	while (true)
	{
		sem_wait(p->vars->sem_forks);
		print_status(p, "has taken a fork");
		sem_wait(p->vars->sem_forks);
		print_status(p, "has taken a fork");
		set_last_eat_time(&state, thread_arg.sem);
		wait_ms(p->vars->eat_time);
		sem_post(p->vars->sem_forks);
		sem_post(p->vars->sem_forks);
		increment_eat_count(&state, thread_arg.sem);
		print_status(p, "is sleeping");
		wait_ms(p->vars->sleep_time);
	}
	while (true)
		;
}
