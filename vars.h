#ifndef VARS_H

# define VARS_H

# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

typedef long long t_time;

struct s_vars;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	struct s_vars	*vars;
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
	t_time	start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		writing_lock;
}	t_vars;

#endif
