#include "philo.h"
#include <pthread.h>
#include <stdio.h> ///+++++++++++++++++++++++++++++++++++++++
#include <stdlib.h>

void	*philo_act(void *param)
{
	return (NULL);
}

void	destroys_mutexes(int i, t_param *param)
{
	int	start;

	start = 0;
	while (start <= i)
	{
		pthread_mutex_destroy(&param->forks[start]);
		++start;
	}
	free(param->forks);
}

int	init_param(t_param *param, t_rule *rule)
{
	int	i;

	param->rule = rule;
	param->forks = malloc(sizeof(pthread_mutex_t) * rule->num_of_philo);
	if (!param->forks)
		return (FAIL);
	i = 0;
	while (i < rule->num_of_philo)
	{
		if(pthread_mutex_init(&param->forks[i], NULL) || i + 1 == rule->num_of_philo)
		{
			destroys_mutexes(i, param);
			return (FAIL);
		}
		++i;
	}
	param->tids = malloc(sizeof(pthread_t) * rule->num_of_philo);
	if (!param->tids)
		return (FAIL);
	return (SUCCESS);
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
		pthread_create(&param.tids[i], NULL, philo_act, NULL);
		++i;
	}
	pthread_join(param.tids[i], NULL);
	return (SUCCESS);
}
