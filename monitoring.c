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
	if (num_of_hogs == param.rule->num_of_philo)
	{
		param.rule->is_dining = FALSE;
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
		// if (param.philo[i].life == DEAD || (param.philo[i].starving_time / 10 >= param.rule->time_to_die))
		if ((param.philo[i].starving_time / 10 >= param.rule->time_to_die))
		{
			// starving_time 체크시 printf 누가 죽었음이 안나옴
			printf("%d : starving_time : %lld\n",i + 1, param.philo[i].starving_time);
			printf("[%lld] %d died\n", get_time() - param.start_time, i + 1);
			param.rule->is_dining = FALSE;
			return (KILL_PROCESS);
		}
		++i;
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