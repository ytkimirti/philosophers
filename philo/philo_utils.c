/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykimirti <ykimirti@42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 18:56:45 by ykimirti          #+#    #+#             */
/*   Updated: 2022/09/14 18:56:46 by ykimirti         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "vars.h"
#include "colors.h"
#include <pthread.h>
#include <time.h>
#include "unistd.h"
#include <stdio.h>
#include "utils.h"

// Uses a mutex to access philo->last_eat_time if
// use_mutex is true
bool	did_philo_starve(t_philo *p, bool use_mutex)
{
	int	diff;

	if (use_mutex)
		pthread_mutex_lock(&p->mutex);
	diff = get_time() - p->last_eat_time;
	if (use_mutex)
		pthread_mutex_unlock(&p->mutex);
	if (diff > p->vars->starve_time)
		return (true);
	return (false);
}
