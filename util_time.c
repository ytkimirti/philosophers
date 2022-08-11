#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include "vars.h"

// 1us is 1000 * 1000 second
// 1ms is 1000us
t_time	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}
