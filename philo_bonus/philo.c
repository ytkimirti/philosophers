/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykimirti <ykimirti@42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:39:35 by ykimirti          #+#    #+#             */
/*   Updated: 2022/08/19 16:57:08 by ykimirti         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "vars.h"
#include <time.h>
#include "unistd.h"
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include "utils.h"
#include <pthread.h>

typedef struct s_state
{
	time_t	last_eat_time;
	t_philo	*philo;
	int		eat_count;
}	t_state;

// No need to terminate with newline
void	print_status(t_philo *philo, char *msg)
{
	sem_wait(philo->vars->sem_writing);
	if (!philo->vars->stop)
		printf("%lld %d %s\n", get_time(), philo->id, msg);
	sem_post(philo->vars->sem_writing);
}

void	wait_ms(int ms)
{
	t_time	start_time;

	start_time = get_time();
	while (get_time() - start_time < ms)
		usleep(30);
}

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

void	philo_entry(t_philo *p)
{
	t_state		state;
	pthread_t	thread;

	state.philo = p;
	state.last_eat_time = get_time();
	pthread_create(&thread, NULL, thread_func, (void *)&state);
	if (p->id % 2 == 0)
		usleep(1000 * (p->vars->eat_time / 2));
	while (true)
	{
		sem_wait(p->vars->sem_forks);
		print_status(p, "has taken a fork");
		sem_wait(p->vars->sem_forks);
		print_status(p, "has taken a fork");

		state.last_eat_time = get_time();
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
