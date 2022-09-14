/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykimirti <ykimirti@42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 18:15:47 by ykimirti          #+#    #+#             */
/*   Updated: 2022/09/14 18:36:22 by ykimirti         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARS_H

# define VARS_H

# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

typedef long long	t_time;

struct				s_vars;

// The mutex is for `last_eat_time` and `is_done`
typedef struct s_philo
{
	int						id;
	bool					is_done;
	t_time					last_eat_time;
	pthread_t				thread;
	struct s_vars			*vars;
	pthread_mutex_t			mutex;
}	t_philo;

// The mutex is for `stop`
typedef struct s_vars
{
	int				count;
	t_philo			*philos;
	int				starve_time;
	int				eat_time;
	int				sleep_time;
	int				max_eat_count;
	bool			is_infinite;
	bool			stop;
	pthread_mutex_t	*forks;
	pthread_mutex_t	writing_lock;
	pthread_mutex_t	mutex;
}	t_vars;

#endif
