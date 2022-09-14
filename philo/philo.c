/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykimirti <ykimirti@42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 18:15:33 by ykimirti          #+#    #+#             */
/*   Updated: 2022/09/14 18:26:11 by ykimirti         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "vars.h"
#include "colors.h"
#include <pthread.h>
#include <time.h>
#include "unistd.h"
#include <stdio.h>
#include "utils.h"

// No need to terminate with newline
void	print_status(t_philo	*philo, char *msg)
{
	if (philo->vars->stop)
		return ;
	pthread_mutex_lock(&philo->vars->writing_lock);
	if (!philo->vars->stop)
		printf("%lld %d %s\n", get_time(), philo->id, msg);
	pthread_mutex_unlock(&philo->vars->writing_lock);
}

void	wait_ms(t_vars *vars, int ms)
{
	t_time	start_time;

	start_time = get_time();
	while (!vars->stop && get_time() - start_time < ms)
		usleep(30);
}

void	philo_eat(t_philo *p)
{
	pthread_mutex_lock(&p->vars->forks[(p->id - 1) % p->vars->count]);
	print_status(p, "has taken a fork");
	pthread_mutex_lock(&p->vars->forks[(p->id - 2) % p->vars->count]);
	print_status(p, "has taken a fork");
	p->last_eat_time = get_time();
	pthread_mutex_unlock(&p->vars->forks[(p->id - 2) % p->vars->count]);
	pthread_mutex_unlock(&p->vars->forks[(p->id - 1) % p->vars->count]);
	wait_ms(p->vars, p->vars->eat_time);
}

// NOTES:
// Fork 0 is at the right of philo one.
// Philo id's start from 1
// The fork at the right of philo 1 is fork 0
// So right fork is (id - 1) % count
// Left fork is (id - 2) % count
void	*philo_loop(void *arg)
{
	t_philo	*p;
	int		eat_count;

	p = (t_philo *)arg;
	eat_count = 0;
	if (p->id % 2 == 0)
		usleep(1000 * (p->vars->eat_time / 2));
	while (!p->vars->stop)
	{
		philo_eat(p);
		eat_count++;
		if (!p->vars->is_infinite && eat_count >= p->vars->max_eat_count)
		{
			p->is_done = true;
			return (NULL);
		}
		print_status(p, "is sleeping");
		wait_ms(p->vars, p->vars->sleep_time);
		print_status(p, "is thinking");
	}
	return (NULL);
}
