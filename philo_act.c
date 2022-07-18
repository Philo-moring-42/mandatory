#include "philo.h"
#include <pthread.h>
#include <stdio.h> ///+++++++++++++++++++++++++++++++++++++++
#include <stdlib.h>

void	*philo_act(void *data)
{
	int		tid;
	t_philo	*philo;

	philo = (t_philo *)data;
	tid = philo->tid_index;
	if (tid % 2 == 0)
	{
		pthread_create
	}
	return (NULL);
}

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
		pthread_create(&param.tids[i], NULL, philo_act, &philo);
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
