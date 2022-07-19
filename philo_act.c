#include "philo.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h> ///+++++++++++++++++++++++++++++++++++++++
#include <stdlib.h>

void	philo_eat(t_rule rule, int tid)
{
	usleep(rule.time_to_eat);
	printf("%d is eating now\n", tid + 1);
}


void	*philo_act(void *data)
{
	int		tid;
	t_philo	*philo;

	philo = (t_philo *)data;
	tid = philo->tid_index;
	if (tid % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		printf("%d get left fork\n" , tid + 1);
		pthread_mutex_lock(philo->right_fork);
		printf("%d get right fork\n" , tid + 1);
	}
	// else
	// {
	// 	pthread_mutex_lock(philo->right_fork);
	// 	pthread_mutex_lock(philo->left_fork);
	// }
	philo_eat(*(philo->param->rule), philo->tid_index);
		//pthread_create
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
		pthread_create(&param.tids[i], NULL, philo_act, param.philo);
	//	pthread_join(param.tids[i], NULL);
		++i;
	}
	i = 0;
	// while (i < rule->num_of_philo)
	// {
	// 	test_philo(param.philo[i], i);
	// 	++i;
	// }
	while (i < rule->num_of_philo)
	{
		pthread_join(param.tids[i], NULL);
		++i;
	}
	return (SUCCESS);
}
