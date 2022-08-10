#ifndef VARS_H

# define VARS_H

# include <pthread.h>
# include <stdbool.h>

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
}	t_philo;

typedef struct s_vars
{
	int			count;
	t_philo		*philos;
	int			starve_time;
	int			eat_time;
	int			sleep_time;
	int			max_eat_count;
	bool		is_infinite;
	long long	start_time;
}	t_vars;

#endif
