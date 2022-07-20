#include "philo.h"
#include <unistd.h>
#include <stdio.h>

int	check_eat_count(t_param param)
{
	int	i;
	int	num_of_hogs;

	num_of_hogs = 0;
	i = 0;
	while (i < param.rule->num_of_philo)
	{
		if (param.philo[i].eat_count >= param.rule->count_of_must_eat)
			++num_of_hogs;
		++i;
	}
	// printf("num_of_hogs : %d\n", num_of_hogs);
	if (num_of_hogs == param.rule->num_of_philo)
	{
		// pthread_mutex_lock(param.dining_or_not);
		param.rule->is_dining = FALSE;
		// pthread_mutex_unlock(param.dining_or_not);
		printf("all philosophers have became hogs\n");
		return (KILL_PROCESS);
	}
	return (KEEP_PROCESS);
}

int	check_death_of_philo(t_param param)
{
	int	i;

	i = 0;
	while (i < param.rule->num_of_philo)
	{
		/* if (param.philo[i].starving_time > param.rule->time_to_die)
		{
			param.rule->is_dining = FALSE;
			printf("philo %d is dead\n", i + 1);
			return (KILL_PROCESS);
		} */
		if (param.philo[i].life == DEAD)
		{
			// pthread_mutex_lock(param.dining_or_not);
			param.rule->is_dining = FALSE;
			// pthread_mutex_unlock(param.dining_or_not);
			return (KILL_PROCESS);
		}
		++i;
		usleep(100);
	}
	return (KEEP_PROCESS);
}

int	monitoring_philos(t_param param)
{
	while (1)
	{
		if (check_death_of_philo(param) == KILL_PROCESS)
			break;
		if (param.rule->if_count_of_must_eat == TRUE && \
			check_eat_count(param) == KILL_PROCESS)
			break;
	}
	return (KILL_PROCESS);
}