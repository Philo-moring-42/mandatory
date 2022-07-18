#include "philo.h"
#include <pthread.h>
#include <stdio.h> ///+++++++++++++++++++++++++++++++++++++++
#include <stdlib.h>

void	*philo_act(void *param)
{
	return (NULL);
}

// void	*philo_act(t_param *param)
// {
// 	t_philo	philo;

// 	init_philo(&philo, *param);
// }

int	philo_run(t_rule *rule)
{
	int			i;
	t_param		param;

	if (init_param(&param, rule) == FAIL)
		return (FAIL);
	i = 0;
	while (i < rule->num_of_philo)
	{
		param.philo[i].tid_index = i;
		pthread_create(&param.tids[i], NULL, philo_act, &param);
		++i;
	}
	i = 0;
	while (i < rule->num_of_philo)
	{
		test_philo(param.philo[i], i);
		++i;
	}
	pthread_join(param.tids[i], NULL);
	return (SUCCESS);
}
