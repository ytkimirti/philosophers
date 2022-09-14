/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykimirti <ykimirti@42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 18:42:31 by ykimirti          #+#    #+#             */
/*   Updated: 2022/09/14 18:44:06 by ykimirti         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include "vars.h"

bool	get_stop_mutex(t_vars *vars)
{
	bool	stop;

	pthread_mutex_lock(&vars->mutex);
	stop = vars->stop;
	pthread_mutex_unlock(&vars->mutex);
	return (stop);
}
