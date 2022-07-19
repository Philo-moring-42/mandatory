#include "philo.h"
#include <sys/time.h>

long long	get_time(void)
{
	struct timeval	time;
	long long		ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec) * 1000 + (time.tv_usec) / 1000;
	return (ms);
}
