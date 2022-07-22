#include "philo.h"
#include <pthread.h>
#include <stdlib.h>

static void	destroy_mutex(int i, t_param *param)
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

static int	init_philo(t_param *param)
{
	int	i;

	param->philo = malloc(sizeof(t_philo) * param->rule->num_of_philo);
	if (!param->philo)
		return (FAIL);
	i = 0;
	while (i < param->rule->num_of_philo)
	{
		param->philo[i].param = param;
		param->philo[i].life = ALIVE;
		param->philo[i].eat_count = 0;
		param->philo[i].start_starving_time = get_time();
		param->philo[i].left_fork = &param->forks[i];
		param->philo[i].right_fork = &param->forks[(i + 1) % param->rule->num_of_philo];
		++i;
	}
	return (SUCCESS);
}


int	init_param(t_param *param, t_rule *rule)
{
	int	i;

	param->rule = rule;
	param->forks = malloc(sizeof(pthread_mutex_t) * rule->num_of_philo);
	pthread_mutex_init(&param->dead_check, NULL);
	pthread_mutex_init(&param->print_lock, NULL);
	if (!param->forks)
		return (FAIL);
	i = 0;
	while (i < rule->num_of_philo)
	{
		if (pthread_mutex_init(&param->forks[i], NULL))
		{
			destroy_mutex(i, param);
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
