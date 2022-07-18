#include "philo.h"
#include <pthread.h>
#include <stdlib.h>

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

static void	init_philo(t_param *param)
{
	param->philo = malloc(sizeof(t_philo) * param->rule->num_of_philo);
	//+++++++++++++++++++++++++++++++++++++++++?
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
		if(pthread_mutex_init(&param->forks[i], NULL))
		{
			destroys_mutexes(i, param);
			return (FAIL);
		}
		++i;
	}
	param->tids = malloc(sizeof(pthread_t) * rule->num_of_philo);
	if (!param->tids)
		return (FAIL);
	init_philo(param);
	return (SUCCESS);
}
