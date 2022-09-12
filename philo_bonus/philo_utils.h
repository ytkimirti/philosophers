/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykimirti <ykimirti@42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:46:42 by ykimirti          #+#    #+#             */
/*   Updated: 2022/09/12 11:47:54 by ykimirti         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_UTILS_H

# define PHILO_UTILS_H

# include "vars.h"

typedef struct s_state
{
	time_t	last_eat_time;
	t_philo	*philo;
	int		eat_count;
	sem_t	*sem_state_read;
}	t_state;

void	wait_ms(int ms);
void	print_status(t_philo *philo, char *msg);
void	set_last_eat_time(t_state *state);

#endif
