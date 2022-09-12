/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykimirti <ykimirti@42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:45:58 by ykimirti          #+#    #+#             */
/*   Updated: 2022/09/12 11:49:22 by ykimirti         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "vars.h"
#include "unistd.h"
#include "semaphores.h"
#include "utils.h"
#include "philo_utils.h"
#include <time.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>

void	wait_ms(int ms)
{
	t_time	start_time;

	start_time = get_time();
	while (get_time() - start_time < ms)
		usleep(30);
}

// No need to terminate with newline
void	print_status(t_philo *philo, char *msg)
{
	sem_wait(philo->vars->sem_writing);
	if (!philo->vars->stop)
		printf("%lld %d %s\n", get_time(), philo->id, msg);
	sem_post(philo->vars->sem_writing);
}

void	set_last_eat_time(t_state *state)
{
	sem_wait(state->sem_state_read);
	state->last_eat_time = get_time();
	sem_post(state->sem_state_read);
}

void	incremenet_eat_count(t_state *state)
{
	sem_wait(state->sem_state_read);
	state->eat_count++;
	sem_post(state->sem_state_read);
}